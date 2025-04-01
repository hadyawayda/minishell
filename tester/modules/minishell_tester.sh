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

    echo -e
    read -rp "Press any key to continue..." ;
}

minishell_tester_menu() {
    while true; do
        clear
        echo -e "${BLUE}----- Minishell Tester -----${NC}"
        echo -e "${GREEN}a) Run All Cases"
        echo -e "1) Echo Cases"
        echo -e "2) \$ expansions"
        echo -e "3) Quotations"
        echo -e "4) Piping"
        echo -e "5) Redirections"
        echo -e "6) AND (&&) / OR (||)"
        echo -e "7) Wildcard"
        echo -e "8) Export / Env"
        echo -e "9) Exit Status Handling"
        echo -e "10) Signals Handling"
        echo -e "11) Mix / Complex Cases${NC}"
        echo -e "${ORANGE}f) Return to Main Menu${GREEN}"
        echo -e
        read -rp "Select an option: " choice
        
        case $choice in
            a)echo -e "${BLUE}Running all test cases..." ;;
            1) file="test_files/echo.xlsx" ;;
            2) file="test_files/dollar_expansion.xlsx" ;;
            3) file="test_files/quotations.xlsx" ;;
            4) file="test_files/piping.xlsx" ;;
            5) file="test_files/redirections.xlsx" ;;
            6) file="test_files/and_or.xlsx" ;;
            7) file="test_files/wildcard.xlsx" ;;
            8) file="test_files/export_env.xlsx" ;;
            9) file="test_files/exit_status.xlsx" ;;
            10) file="test_files/signals.xlsx" ;;
            11) file="test_files/complex_cases.xlsx" ;;
            f) break ;;
            *) echo "Invalid option." ; continue ;;
        esac
        
        run_test_case "$file"
    done
}
