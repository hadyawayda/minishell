#!/usr/bin/env bash

execute_test_cases() {
  local input_csv="$1"
  local output_csv="$2"
  local valgrind_enabled="$3"
  local test_index=1
  local passed_tests=0
  local total_tests=0

  # Open both input and output files
  exec 3< "$input_csv"
  exec 4< "$output_csv"

  while IFS= read -r test_input <&3; do
    ((total_tests++))

    # Remove `$>` prefix and trailing `ǂ`
    test_input="${test_input#\$> }"
    test_input="${test_input%ǂ}"

    # Read expected output, accumulating lines until `$>ǂ` delimiter is encountered
    expected_output=""
    # while IFS= read -r line <&4; do
    #     if [[ "$line" == *"\$>ǂ" ]]; then
    #         expected_output+="${line%\$>ǂ}"
    #         break
    #     else
    #         expected_output+="$line"$'\n'  # Preserve multiline expected outputs
    #     fi
    # done

    # Remove any trailing newline character from expected_output
    # expected_output=$(echo -n "$expected_output")
    # Comment the next line to disable the actual bash output and use the one from the excel file
    expected_output=$(echo "$test_input" | bash 2>&1)

    # Run minishell and capture output (uncomment second line to override with actualy minishell output)
    # actual_output=$(echo "$test_input" | bash 2>&1)
    # Strip minishell prompt from actual output (both leading & trailing prompts)
    actual_output=$(echo "$test_input" | ../minishell 2>&1)
    actual_output=$(
      echo "$actual_output" \
      | sed -E '
        # 1) Remove ANSI color codes
        s/\x1b\[[0-9;]*m//g;

        # 2) Delete the first line, whatever it is
        1d;

        # 3) On each remaining line, remove "MiniHell>" and everything after
        s/MiniHell>.*//
      '
    )


    # actual_output=$(echo "$test_input" | ../michel 2>&1)

    # Run Valgrind if enabled
    if [[ "$valgrind_enabled" == "1" ]]; then
      leaks=$(valgrind --leak-check=full --error-exitcode=42 ./michel "$test_input" 2>&1 | grep "definitely lost" || echo "No leaks detected")
    else
      leaks="No leaks detected"
    fi

    # Compare results
    local pass_output=false
    local pass_leak=false

    [[ "$actual_output" == "$expected_output" ]] && pass_output=true
    [[ "$leaks" == "No leaks detected" || "$valgrind_enabled" == "0" ]] && pass_leak=true

    # Determine overall pass/fail
    if $pass_output && $pass_leak; then
      overall_pass=true
      ((passed_tests++))
    else
      overall_pass=false
    fi

    # Print results with colors
    if $overall_pass; then
      echo -e "${GREEN}Test #$test_index${RESET}   Command:  [${test_input}]"
    else
      echo -e "${RED}Test #$test_index${RESET}   Command:  [${test_input}]"
    fi

    # Print Expected vs Actual vs Leaks
    local color_output=$([[ $pass_output == true ]] && echo "$GREEN" || echo "$RED")
    local color_leak=$([[ $pass_leak == true ]] && echo "$GREEN" || echo "$RED")
    
    echo -e "${color_output}Expected:${RESET} [${expected_output}]\n${color_output}Actual:${RESET} [${actual_output}]"
    if [[ "$valgrind_enabled" == "1" ]]; then
      echo -e "${color_leak}Leaks:${RESET} [${leaks}]"
    fi

    echo
    ((test_index++))
  done

  exec 3<&-  # Close input file
  exec 4<&-  # Close output file

  echo -e "${GREEN}All done.${RESET}"
  echo -e "Passed ${GREEN}${passed_tests}${RESET} out of ${total_tests} tests."
}
