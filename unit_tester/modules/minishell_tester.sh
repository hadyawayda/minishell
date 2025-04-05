#!/usr/bin/env bash

run_test_case() {
    local file="$1"

    input_csv="${file%.xlsx}_input.csv"
    output_csv="${file%.xlsx}_output.csv"

    echo -e 

    # Convert Excel to CSV (if needed)
    if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
        convert_excel_to_csv "$file"
    fi
    
    # Check if conversion was successful
    if [[ $? -ne 0 ]]; then
        echo -e "${Green}Press any key to continue..."
        read -rp "" ;
        return 1
    fi

    # Check if CSV files exist before proceeding
    if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
        echo -e "${RED}Error: CSV files '$input_csv' or '$output_csv' do not exist after conversion.${ORANGE}"
        read -rp "Press any key to continue..." ;
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

run_all_test_cases() {
    local dir="test_files"
    
    if [[ ! -d "$dir" ]]; then
        echo -e "${RED}Error: Directory '$dir' not found.${NC}"
        return 1
    fi

    local files=("$dir"/all.xlsx)

    if [[ ${#files[@]} -eq 0 ]]; then
        echo -e "${ORANGE}No .xlsx test files found in $dir.${NC}"
        return 1
    fi

    for file in "${files[@]}"; do
        echo -e "${CYAN}Running test file: $file${NC}"
        run_test_case "$file"
    done

	echo -e
	read -n 1 -rsp "Press any key to return to the menu..." ;
}

minishell_tester_menu() {
    while true; do
        clear
        echo -e "${BLUE}----- Minishell Tester -----${GREEN}"
        echo -e "a) ${CYAN}Run All Cases"
        echo -e "${GREEN}1) Echo & \$ & Quotation Cases"
        echo -e "2) Piping"
        echo -e "3) Redirections"
        echo -e "4) AND (&&) / OR (||)"
        echo -e "5) Wildcard"
        echo -e "6) Export / Env"
        echo -e "7) Exit Status Handling"
        echo -e "8) Signals Handling"
        echo -e "9) Mix / Complex Cases${NC}"
        echo -e "${ORANGE}f) Return to Main Menu${GREEN}"
        echo -e
        read -rp "Select an option: " choice
        
        case $choice in
            a) echo -e "${BLUE}Running all test cases..."
                run_all_test_cases
                continue ;;
            1) file="test_files/program/echo.xlsx" ;;
            2) file="test_files/program/piping.xlsx" ;;
            3) file="test_files/program/redirections.xlsx" ;;
            4) file="test_files/program/and_or.xlsx" ;;
            5) file="test_files/program/wildcard.xlsx" ;;
            6) file="test_files/program/export_env.xlsx" ;;
            7) file="test_files/program/exit_status.xlsx" ;;
            8) file="test_files/program/signals.xlsx" ;;
            9) file="test_files/program/complex_cases.xlsx" ;;
            f) break ;;
            *) echo "Invalid option." ; continue ;;
        esac
        
        run_test_case "$file"

        echo -e
		read -n 1 -rsp "Press any key to return to the menu..." ;
    done
}
