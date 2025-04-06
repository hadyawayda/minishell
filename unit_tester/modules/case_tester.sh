#!/usr/bin/env bash

run_test_case() {
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
}


run_all_cases() {
    local test_dir="$1"

    local files=("$test_dir"/*.xlsx)
    if [[ "${files[0]}" == "$test_dir/*.xlsx" || ${#files[@]} -eq 0 ]]; then
        echo -e "${RED}\\nNo test files found in '$test_dir'.${NC}"
        return 1
    fi

    for file in "${files[@]}"; do
        echo -e "\\n${BLUE}Running test file: ${YELLOW}$(basename "$file")${BLUE}"
        run_test_case "$file"
        echo -e "${CYAN}"
        read -n 1 -rsp "Press any key to continue to next case..."
    done
}
