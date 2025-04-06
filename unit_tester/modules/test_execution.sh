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
	local is_bonus_case=false
	
	if [[ "$test_input" == *"*"* ]]; then
	  is_bonus_case=true
	fi

	# Check if the current test case contains sleep command and skip it
	if [[ "$test_input" == *"sleep"* ]]; then
	  # Read and discard the corresponding output line from FD #4
	  # to keep the file descriptors in sync.
	  IFS= read -r _discard <&4
	  echo
	  continue
	fi

	if [[ "$is_bonus_case" == true && "$BONUS_TESTING_ENABLED" -eq 0 ]] || [[ "$test_input" == *"sleep"* ]]; then
	  # Read and discard the corresponding output line from FD #4
	  # to keep the file descriptors in sync.
	  IFS= read -r _discard <&4
	  echo
	  continue
	fi

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

	actual_output=$(echo "$test_input" | ../../../minishell 2>&1)

	# Strip minishell prompt from actual output (both leading & trailing prompts) 
	# And remove ANSI color codes & partial lines
	actual_output=$(
	  echo "$actual_output" \
	  | sed -E "
		# 1) Remove ANSI color codes
		s/\x1b\[[0-9;]*m//g;

		# 2) Delete the first line, whatever it is
		1d;

		# 3) On each remaining line, remove \"$PROGRAM_PROMPT\" and everything after '$PROGRAM_PROMPT'
		s|${PROGRAM_PROMPT//|\\|}.*||
	  "
	)

	# Valgrind if enabled
	local leaks="No leaks detected"
	if [[ "$valgrind_enabled" == "1" ]]; then
	  leaks= $(valgrind --leak-check=full --error-exitcode=42 ./michel "$test_input" 2>&1 | grep "definitely lost" || echo "No leaks detected")
	fi

	# Compare results
	local pass_output=false
	local pass_leak=false

	# A: Partial match if they both contain "syntax error"
	if [[ "$expected_output" == *"syntax error"* && "$actual_output" == *"syntax error"* ]]; then
		pass_output=true

	# B: Partial match if they both contain "command not found"
	elif [[ "$expected_output" == *"command not found"* && "$actual_output" == *"command not found"* ]]; then
		pass_output=true

	# C: Otherwise do exact match
	elif [[ "$actual_output" == "$expected_output" ]]; then
		pass_output=true
	fi

	[[ "$leaks" == "No leaks detected" || "$valgrind_enabled" == "0" ]] && pass_leak=true

	# Determine overall pass/fail
	local overall_pass=false
	if $pass_output && $pass_leak; then
      overall_pass=true
      ((passed_tests++))
    fi

	# Print results with colors
	if $overall_pass; then
	  echo -e "${BLUE}Test #$test_index${RESET}   Command:  [${test_input}]"
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
