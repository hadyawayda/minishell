#!/usr/bin/env bash

# Run Tokenization Tests
run_tokenization_tests() {
    while true; do
        # clear
        echo -e "${BLUE}----- Tokenization Tester -----${NC}"
        echo -e "${GREEN}1) Echo Cases"
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
        echo -e "${RED}0) Return to Main Menu${NC}"
        read -rp "Select an option: " choice

        case $choice in
            1) file="test_files/tokenization_echo.xlsx" ;;
            2) file="test_files/tokenization_dollar_expansion.xlsx" ;;
            3) file="test_files/tokenization_quotations.xlsx" ;;
            4) file="test_files/tokenization_piping.xlsx" ;;
            5) file="test_files/tokenization_redirections.xlsx" ;;
            6) file="test_files/tokenization_and_or.xlsx" ;;
            7) file="test_files/tokenization_wildcard.xlsx" ;;
            8) file="test_files/tokenization_export_env.xlsx" ;;
            9) file="test_files/tokenization_exit_status.xlsx" ;;
            10) file="test_files/tokenization_signals.xlsx" ;;
            11) file="test_files/tokenization_complex_cases.xlsx" ;;
            0) break ;;
            *) echo "Invalid option." ; continue ;;
        esac

        input_csv="${file%.xlsx}_input.csv"
        output_csv="${file%.xlsx}_output.csv"

        # Convert Excel to CSV (if needed)
        if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
            convert_excel_to_csv "$file"
        fi

        # Check if CSV files exist before proceeding
        if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
            echo -e "${RED}Error: CSV files '$input_csv' or '$output_csv' do not exist after conversion.${NC}"
            continue
        fi

        # Run test cases with input and output CSVs
        execute_test_cases "$input_csv" "$output_csv" "$VALGRIND_ENABLED"
    done
}

tokenization_tester_menu() {
	echo "Running Tokenization tests..."
    while true; do
        # clear
        echo -e "${BLUE}----- Tokenization Tester -----${NC}"
        echo -e "${GREEN}1) Run tokenization tests"
        echo -e "2) Set tokenization file path"
        echo -e "3) Set token struct header path${NC}"
        echo -e "${RED}0) Return to Main Menu${NC}"
        
        read -rp "Option: " choice
        
        case $choice in
            1) run_tokenization_tests ;; 
            2) read -rp "Enter tokenization file path: " TOKEN_FILE ;;
            3) read -rp "Enter struct header path: " TOKEN_STRUCT ;;
            0) break ;;
            *) echo "Invalid option." ;;
        esac
    done
}
