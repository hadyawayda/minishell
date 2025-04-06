#!/usr/bin/env bash

run_test_case() {
    local file="$1"

    # Derive filename without .xlsx suffix
    local filename_base
    filename_base=$(basename "$file" .xlsx)

    # Place the generated CSV files in test_files/files/...
    local input_csv="tester_files/converted_files/${filename_base}_input.csv"
    local output_csv="tester_files/converted_files/${filename_base}_output.csv"

    # Convert Excel to CSV (if needed)
    if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
        convert_excel_to_csv "$file"
		# Check if conversion was successful
		if [[ $? -ne 0 ]]; then
			return 1
		fi
    fi

    # Check if CSV files exist before proceeding
    if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
        echo -e "\\n${RED}Error: CSV files '$input_csv' or '$output_csv' do not exist after conversion.${ORANGE}"
        return 1
    fi

    # Run test cases with input and output CSVs
    execute_test_cases "$input_csv" "$output_csv" "$VALGRIND_ENABLED"

    # Remove temporary CSV files
	rm -rf tester_files

    # Check if the temporary files were removed successfully
    if [[ $? -ne 0 ]]; then
        echo -e "${RED}Error: Failed to remove temporary files.${NC}"
    fi
}

run_all_cases() {
    local case_type="$1"

    # Original working directory (unit_tester/)
    local original_dir="$(pwd)"

    # Ensure tester_files/converted_files exists
    mkdir -p "tester_files/converted_files"

    # Change into tester_files/
    cd "tester_files" || { echo "Failed to enter tester_files directory"; return 1; }

    # Directory of the XLSX test files (from tester_files/, go up one level)
    local dir="../test_files/$case_type"
    if [[ ! -d "$dir" ]]; then
        echo -e "${RED}Error: Directory '$dir' does not exist.${NC}"
        cd "$original_dir" || exit
        read -n 1 -rsp "Press any key to continue..."
        return 1
    fi

    # Expand XLSX file patterns
    local files=("$dir"/*.xlsx)

    # Check if files exist
    if [[ "${files[0]}" == "$dir/*.xlsx" ]] || [[ ${#files[@]} -eq 0 ]]; then
        echo -e "${RED}\\n\\nNo $case_type test files found in $dir.\\n${ORANGE}"
        cd "$original_dir" || exit
        read -n 1 -rsp "Press any key to continue..."
        return 1
    fi

    # Run test cases
    for i in "${!files[@]}"; do
        local file="${files[$i]}"

        if [[ $i -gt 0 ]]; then
            echo -e "${CYAN}\\n"
            read -n 1 -rsp "Press any key to continue to next case..."
        fi

        echo -e "\\n\\n${BLUE}Running test file: ${YELLOW}$file"

        # Execute the test from within tester_files
        run_test_case "$file"
    done

    # Return to original directory
    cd "$original_dir" || exit

    # Clean up tester_files after execution
    rm -rf "tester_files"

    echo -e "${ORANGE}"
    read -n 1 -rsp "Press any key to return to the menu..."
}
