#!/usr/bin/env bash

execute_test_cases() {
  local input_csv="$1"
  local output_csv="$2"
  local valgrind_enabled="$3"
  local test_index=1
  local passed_tests=0
  local total_tests=0

  # Open both input and output files using file descriptors 3 and 4
  exec 3< "$input_csv"
  exec 4< "$output_csv"

  while IFS= read -r test_input <&3; do
    local is_bonus_case=false
    
    if [[ "$test_input" == *"*"* ]]; then
      is_bonus_case=true
    fi

    if [[ "$is_bonus_case" == true && "$BONUS_TESTING_ENABLED" -eq 0 ]] || [[ "$test_input" == *"sleep"* ]]; then
      IFS= read -r _discard <&4
      echo
      continue
    fi

    ((total_tests++))

    # Remove "$> " prefix and trailing "ǂ"
    test_input="${test_input#\$> }"
    test_input="${test_input%ǂ}"

    # Use bash to compute the expected output (modify if needed)
    expected_output=$(echo "$test_input" | bash 2>&1)

    # Run minishell and capture output using the absolute path from ROOT_DIR
    actual_output=$(echo "$test_input" | "$ROOT_DIR/minishell" 2>&1)

    # Strip ANSI color codes and any prompt-related artifacts
    actual_output=$(
      echo "$actual_output" | sed -E "
        s/\x1b\[[0-9;]*m//g;
        1d;
        s|${PROGRAM_PROMPT//|\\|}.*||
      "
    )

    # If valgrind is enabled, check for memory leaks using the michel binary
    local leaks="No leaks detected"
    if [[ "$valgrind_enabled" == "1" ]]; then
      leaks=$(valgrind --leak-check=full --error-exitcode=42 "$ROOT_DIR/michel" "$test_input" 2>&1 | grep "definitely lost" || echo "No leaks detected")
    fi

    local pass_output=false
    local pass_leak=false

    # Partial match if both contain "syntax error"
    if [[ "$expected_output" == *"syntax error"* && "$actual_output" == *"syntax error"* ]]; then
      pass_output=true
    # Partial match if both contain "command not found"
    elif [[ "$expected_output" == *"command not found"* && "$actual_output" == *"command not found"* ]]; then
      pass_output=true
    # Otherwise require exact match
    elif [[ "$actual_output" == "$expected_output" ]]; then
      pass_output=true
    fi

    [[ "$leaks" == "No leaks detected" || "$valgrind_enabled" == "0" ]] && pass_leak=true

    local overall_pass=false
    if $pass_output && $pass_leak; then
      overall_pass=true
      ((passed_tests++))
    fi

    # Print test result
    if $overall_pass; then
      echo -e "${BLUE}Test #$test_index${RESET}   Command:  [${test_input}]"
    else
      echo -e "${RED}Test #$test_index${RESET}   Command:  [${test_input}]"
    fi

    local color_output=$([[ $pass_output == true ]] && echo "$GREEN" || echo "$RED")
    local color_leak=$([[ $pass_leak == true ]] && echo "$GREEN" || echo "$RED")
	
    echo -e "${color_output}Expected:${RESET} [${expected_output}]\n${color_output}Actual:${RESET} [${actual_output}]"
    if [[ "$valgrind_enabled" == "1" ]]; then
      echo -e "${color_leak}Leaks:${RESET} [${leaks}]"
    fi

    echo
    ((test_index++))
  done

  # Close the file descriptors
  exec 3<&-
  exec 4<&-

  echo -e "${GREEN}All done.${RESET}"
  echo -e "Passed ${GREEN}${passed_tests}${RESET} out of ${total_tests} tests."
}
