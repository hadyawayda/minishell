#!/usr/bin/env bash

execute_test_cases() {
  echo "Executing test cases..."
  local csv_file="$1"
  local valgrind_enabled="$2"
  local test_index=1
  local passed_tests=0
  local total_tests=0

  # Read test cases from CSV and execute directly
  while IFS=, read -r test_input expected_output; do
    ((total_tests++))

    # Run minishell and capture output
    actual_output=$(echo "$test_input" | ./minishell 2>&1)

    # Run Valgrind if enabled
    if [[ "$valgrind_enabled" == "1" ]]; then
      leaks=$(valgrind --leak-check=full --error-exitcode=42 ./minishell "$test_input" 2>&1 | grep "definitely lost" || echo "No leaks detected")
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
    
    echo -e "${color_output}Expected:${RESET} [${expected_output}]  ${color_output}Actual:${RESET} [${actual_output}]"
    if [[ "$valgrind_enabled" == "1" ]]; then
      echo -e "${color_leak}Leaks:${RESET} [${leaks}]"
    fi

    echo
    ((test_index++))
  done < "$csv_file"

  echo -e "${GREEN}All done.${RESET}"
  echo -e "Passed ${GREEN}${passed_tests}${RESET} out of ${total_tests} tests."
}
