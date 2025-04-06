#!/usr/bin/env bash

run_test_case() {
    local file="$1"

    # Derive filename without .xlsx suffix
    local filename_base
    filename_base=$(basename "$file" .xlsx)

    # Place the generated CSV files in test_files/files/...
    local input_csv="test_files/converted_files/${filename_base}_input.csv"
    local output_csv="test_files/converted_files/${filename_base}_output.csv"

    # Convert Excel to CSV (if needed)
    if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
        convert_excel_to_csv "$file"
    fi

    # Check if conversion was successful
    if [[ $? -ne 0 ]]; then
        return 1
    fi

    # Check if CSV files exist before proceeding
    if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
        echo -e "\\n${RED}Error: CSV files '$input_csv' or '$output_csv' do not exist after conversion.${ORANGE}"
        return 1
    fi

    # Run test cases with input and output CSVs
    execute_test_cases "$input_csv" "$output_csv" "$VALGRIND_ENABLED"

    # Remove temporary CSV files
    rm -f "$input_csv" "$output_csv"
    
    # Check if the temporary files were removed successfully
    if [[ $? -ne 0 ]]; then
        echo -e "${RED}Error: Failed to remove temporary files.${NC}"
    fi
}

run_all_cases() {
    local case_type="$1"
    
    # Create converted_files if needed
    if [[ ! -d "test_files/converted_files" ]]; then
        mkdir -p "test_files/converted_files"
    fi

    # Directory where the XLSX test files are located
    local dir="test_files/$case_type"
    if [[ ! -d "$dir" ]]; then
        echo -e "${RED}Error: Directory '$dir' does not exist.${NC}"
        read -n 1 -rsp "Press any key to continue..."
        return 1
    fi

    # Expand the pattern for the relevant XLSX files
    local files=($dir/*.xlsx)

    # If the pattern doesn't match anything, Bash leaves it as literal
    # Check if it still equals "$dir/*.xlsx" or the array is empty
    if [[ "${files[0]}" == "$dir/*.xlsx" ]] || [[ ${#files[@]} -eq 0 ]]; then
        echo -e "${RED}\\n\\nNo $case_type test files found in $dir (looking for 'echo.xlsx').\\n${ORANGE}"
        read -n 1 -rsp "Press any key to continue..."
        return 1
    fi

    for i in "${!files[@]}"; do
		file="${files[$i]}"
		
		# For files after the first one (index > 0), show the prompt
		if [[ $i -gt 0 ]]; then
			echo -e "${CYAN}\\n"
			read -n 1 -rsp "Press any key to continue to next case..."
		fi
		
		echo -e "\\n\\n${BLUE}Running test file: ${YELLOW}$file"

		# Actually run the test
		run_test_case "$file"
	done

    echo -e "${ORANGE}"
    read -n 1 -rsp "Press any key to return to the menu..."
}
