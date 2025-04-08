#!/usr/bin/env bash

run_test_case() {
    local no_pause="$2"
    if [[ "$no_pause" != "true" ]]; then
	    clear
    fi

    local file="$1"
    local filename_base=$(basename "$file" .xlsx)

    local input_csv="$CONVERTED_FILES_DIR/${filename_base}_input.csv"
    local output_csv="$CONVERTED_FILES_DIR/${filename_base}_output.csv"

    # Convert Excel to CSV if needed
    if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
        convert_excel_to_csv "$(realpath "$file")" || return 1
    fi

    # Confirm CSV files exist
    if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
        echo -e "${RED}CSV files missing after conversion.${NC}"
        return 1
    fi

    # Execute the test cases (assuming execute_test_cases is defined elsewhere)
    execute_test_cases "$input_csv" "$output_csv" "$VALGRIND_ENABLED"

    if [[ "$no_pause" != "true" ]]; then
        echo -e "\\n\\n\\n${CYAN}All $filename_base cases done."
        echo -e "Passed $PASSED_TESTS out of $TOTAL_TESTS tests."
        echo -e "${GREEN}"
        read -n 1 -rsp "Would you like to have a summary of the failed test cases? (y/n) " response
    fi
}

run_all_cases() {
    local test_dir="$1"
    local no_pause="$2"

    local files=("$test_dir"/*.xlsx)
    if [[ "${files[0]}" == "$test_dir/*.xlsx" || ${#files[@]} -eq 0 ]]; then
        echo -e "${RED}\\nNo test files found in '$test_dir'.${NC}"
        return 1
    fi

    for file in "${files[@]}"; do
        echo -e "\\n${BLUE}Now testing: ${YELLOW}$(basename "$file")${BLUE}\\n"
        run_test_case "$file" "$no_pause"
        if [[ "$no_pause" != "true" ]]; then
            echo -e "${CYAN}"
            read -n 1 -rsp "Would you like to have a summary of the failed test cases? (y/n) " response
            PASSED_TESTS=0
            TOTAL_TESTS=0
            clear
        fi
    done
}

execute_test() {
    PASSED_TESTS=0
    TOTAL_TESTS=0
    local test_type="$1"
    local test_arg="$2"
    local no_pause="$3"
    local original_dir="$(pwd)"
    local test_dir

    # Determine test directory based on test type
    if [[ "$test_type" == "program" ]]; then
         test_dir="$PROGRAM_TEST_DIR"
    elif [[ "$test_type" == "tokenization" ]]; then
         test_dir="$TOKENIZATION_TEST_DIR"
    else
         echo "Invalid test type: $test_type"
         return 1
    fi

    # Create and enter the isolated execution directory
    mkdir -p "$EXECUTION_DIR"
    mkdir -p "$CONVERTED_FILES_DIR"
    cd "$EXECUTION_DIR" || { echo "Cannot enter execution directory"; return 1; }

    if [[ "$test_arg" == "all" ]]; then
        run_all_cases "$test_dir" "$no_pause"
        if [[ "$no_pause" == "true" ]]; then
            echo -e "${GREEN}All done."
            echo -e "Passed $PASSED_TESTS out of $TOTAL_TESTS tests."
        fi
    else
        local file="$test_dir/$test_arg"
        if [[ ! -f "$file" ]]; then
            echo -e "${RED}Test file '$file' not found.${NC}"
            cd "$original_dir" || exit
            return 1
        fi
        run_test_case "$file" "$no_pause"
    fi

    # Return to original directory and clean up the tester_files directory
    cd "$original_dir" || exit
    rm -rf "$TESTER_FILES_DIR"
        
    if [[ "$no_pause" != "true" ]]; then
        echo -e "${CYAN}"
        read -n 1 -rsp "Press any key to return to the menu..." ;
    fi
}
