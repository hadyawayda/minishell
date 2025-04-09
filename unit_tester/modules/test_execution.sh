#!/usr/bin/env bash

run_one_case() {
  local cmd_block="$1"
  local test_index="$2"
  local valgrind_enabled="$3"
  local file="$4"

  # 1) Compute expected output using bash
  local expected_output="$(echo -e "$cmd_block" | bash 2>&1)"

  # 2) Run your minishell on the same block
  local actual_output="$(echo -e "$cmd_block" | "$ROOT_DIR/minishell" 2>&1)"

  # 3) Strip ANSI color codes and prompt lines
  actual_output="$(
    echo "$actual_output" | sed -E "
      s/\x1b\[[0-9;]*m//g;   # remove ANSI color codes
      1d;                   # remove the first line
      s|${PROGRAM_PROMPT//|\\|}.*||
    "
  )"

  # 4) If valgrind is enabled, check memory leaks using michel
  local leaks="No leaks detected"
  if [[ "$valgrind_enabled" == "1" ]]; then
    leaks="$(
      echo "$cmd_block" | valgrind --leak-check=full --error-exitcode=42 "$ROOT_DIR/michel" 2>&1 \
      | grep 'definitely lost' || echo 'No leaks detected'
    )"
  fi

  # 5) Compare outputs (partial match for errors, or exact match)
  local pass_output=false

  if [[ "$expected_output" == *"syntax error near unexpected token"* && "$actual_output" == *"syntax error near unexpected token"* ]]; then
    pass_output=true
  elif [[ "$expected_output" == *"command not found"* && "$actual_output" == *"command not found"* ]]; then
    pass_output=true
  elif [[ "$expected_output" == *"No such file or directory"* && "$actual_output" == *"No such file or directory"* ]]; then
    pass_output=true
  elif [[ "$expected_output" == *"Is a directory"* && "$actual_output" == *"Is a directory"* ]]; then
    pass_output=true
  elif [[ "$expected_output" == *"invalid option"* && "$actual_output" == *"invalid option"* ]]; then
    pass_output=true
  elif [[ "$expected_output" == *"not a valid identifier"* && "$actual_output" == *"not a valid identifier"* ]]; then
    pass_output=true
  elif [[ "$expected_output" == *"numeric argument required"* && "$actual_output" == *"numeric argument required"* ]]; then
    pass_output=true
  elif [[ "$expected_output" == *"too many arguments"* && "$actual_output" == *"too many arguments"* ]]; then
    pass_output=true
  elif [[ "$expected_output" == *"ambiguous redirect"* && "$actual_output" == *"ambiguous redirect"* ]]; then
    pass_output=true
  elif [[ "$expected_output" == *"here-document at line 1 delimited by end-of-file"* && "$actual_output" == *"here-document at line 1 delimited by end-of-file"* ]]; then
    pass_output=true
  elif [[ "$actual_output" == "$expected_output" ]]; then
    pass_output=true
  fi

  local pass_leak=false
  if [[ "$leaks" == "No leaks detected" || "$valgrind_enabled" == "0" ]]; then
    pass_leak=true
  fi

  local overall_pass=false
  if $pass_output && $pass_leak; then
    overall_pass=true
  fi

  # 6) Print results
  if $overall_pass; then
    echo -ne "${GREEN}"
    if [[ "$DEBUGGING" == "1" ]]; then
      echo -ne "${BLUE}"
    fi
    echo -ne "Test #$test_index"
    if (( test_index > 9 )); then
      echo -ne "\\t"
    else
      echo -ne "\\t\\t"
    fi
    echo -e "[${cmd_block}]"
    PASSED_TESTS=$((PASSED_TESTS+1))
  else
    echo -ne "${RED}"
    if [[ "$DEBUGGING" == "1" ]]; then
      echo -ne "${BLUE}"
    fi
    echo -ne "Test #$test_index"
    if (( test_index > 9 )); then
      echo -ne "\\t"
    else
      echo -ne "\\t\\t"
    fi
    echo -e "[${cmd_block}]"
  fi

  local color_output=$([[ $pass_output == true ]] && echo "$GREEN" || echo "$RED")
  local color_leak=$([[ $pass_leak == true ]] && echo "$GREEN" || echo "$RED")

  if [[ "$DEBUGGING" == "1" ]]; then
    echo -e "${GREEN}Expected:\\t[${expected_output}]"
    echo -e "${color_output}Actual:\\t\\t[${actual_output}]"
  fi
  
  if [[ "$valgrind_enabled" == "1" ]]; then
    echo -e "${color_leak}Leaks:\\t[${leaks}]"
  fi

  if [[ "$DEBUGGING" == "1" ]]; then
    echo
  fi

  # 7) Log failure details if the test failed.
  if ! $overall_pass; then
    {
	    echo -ne "$file test #$test_index:"
      if (( test_index > 9 )); then
        echo -ne "\\t"
      else
        echo -ne "\\t"
      fi
      echo -e "[${cmd_block}]"
      if [[ "$DEBUGGING" == "1" ]]; then
        echo -e "Expected:\\t[${expected_output}]"
        echo -e "Actual:\\t\\t[${actual_output}]"
      fi
      if [[ "$valgrind_enabled" == "1" ]]; then
        echo -e "Leaks:\\t[${leaks}]\\n"
      fi
      if [[ "$DEBUGGING" == "1" ]]; then
        echo
      fi
    } >> "$FAILED_SUMMARY_FILE"
  fi
}

###############################################################################
# execute_test_cases
#   Reads an input CSV line by line, grouping them into blocks separated
#   by the delimiter (default is "ǂ" at line's end). For each block, calls
#   run_one_case() to run the entire block in one shell session.
#
# Arguments:
#   1) input_csv
#   2) valgrind_enabled
#
# Uses run_one_case() to process each block.
###############################################################################
execute_test_cases() {
  local input_csv="$1"
  local valgrind_enabled="$2"
  local test_index=1
  local delimiter="ǂ"
  local file=$(basename "$3" .xlsx)

  # Open the input CSV using file descriptor 3
  exec 3< "$input_csv"

  while true; do
    local test_block=""
    local skip_case=false

    # Read lines until we find one that ends with the delimiter
    while IFS= read -r line <&3; do
      # If we hit EOF with no line, break out
      if [[ -z "$line" && -z "$test_block" ]]; then
        break 2  # break outer while
      fi

	    if  [[ "$line" == *"sleep"* ]] || 
          [[ "${BONUS_TESTING_ENABLED:-0}" -eq 0 && 
          ("$line" == *"*"* || "$line" == *"&&"* || "$line" == *"||"* || "$line" == *"("* || "$line" == *")"*) ]]; then
        skip_case=true
		    break
      fi

      if [[ "$line" == *"$delimiter" ]]; then
        # Remove the trailing delimiter
        line="${line%$delimiter}"

        # Append this final line to test_block
        test_block+="$line"$'\n'
        break
      else
        test_block+="$line"$'\n'
      fi
    done

	  if $skip_case; then
      continue
    fi

    # If we didn't accumulate anything, we might be at EOF
    if [[ -z "$test_block" ]]; then
      break
    fi

    TOTAL_TESTS=$((TOTAL_TESTS+1))

    # For each line, remove leading "$> " if present
    # We'll do that for the entire block
    local cleaned_block="$(echo "$test_block" | sed 's/^\$> //')"

    # run the entire block as one case
    run_one_case "$cleaned_block" "$test_index" "$valgrind_enabled" "$file"
    ((test_index++))
  done

  exec 3<&-
}
