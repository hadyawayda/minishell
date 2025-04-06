#!/usr/bin/env bash

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
    	read -n 1 -rp "Select an option: " choice
        
        case $choice in
            a) echo -e "${BLUE}\\n\\nRunning all test cases..."
                run_all_cases "program"
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

        echo -e "${ORANGE}"
		read -n 1 -rsp "Press any key to return to the menu..." ;
    done
}
