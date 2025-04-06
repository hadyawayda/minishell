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
            a) execute_test "program" "all";;
            1) execute_test "program" "echo.xlsx";;
            2) execute_test "program" "../all.xlsx";;
            3) execute_test "program" "redirections.xlsx";;
            4) execute_test "program" "and_or.xlsx";;
            5) execute_test "program" "wildcard.xlsx";;
            6) execute_test "program" "export_env.xlsx";;
            7) execute_test "program" "exit_status.xlsx";;
            8) execute_test "program" "signals.xlsx";;
            9) execute_test "program" "complex_cases.xlsx";;
            f) break ;;
            *) echo -e "${RED}Invalid option.${NC}" ;;
        esac
        
        echo -e "${ORANGE}"
		read -n 1 -rsp "Press any key to return to the menu..." ;
    done
}
