#!/usr/bin/env bash

minishell_tester_menu() {
    while true; do
        clear
        echo -e "${BLUE}----- Minishell Tester -----${GREEN}"
        echo -e "a) ${CYAN}Run All Cases"
        echo -e "${GREEN}1) Echo (108 Cases)"
        echo -e "2) CD (121 Cases)"
        echo -e "3) Environment Variables (251 Cases)"
        echo -e "4) Execution (108 Cases)"
        echo -e "5) Exit Status (53 Cases)"
        echo -e "6) Expansion (10 Cases)"
        echo -e "7) PWD (11 Cases)"
        echo -e "8) Redirections (399 Cases)"
        echo -e "9) Signals (10 Cases)"
        echo -e "10) Complex Cases (1 Case)"
        echo -e "0) Basic Cases (57 Cases)${NC}"
        echo -e "${ORANGE}f) Return to Main Menu${GREEN}"
        echo -e
    	read -n 1 -rp "Select an option: " choice
        
        case $choice in
            a) execute_test "program" "all";;
            1) execute_test "program" "echo.xlsx";;
            2) execute_test "program" "cd.xlsx";;
            3) execute_test "program" "env_export_unset.xlsx";;
            4) execute_test "program" "execution.xlsx";;
            5) execute_test "program" "exit.xlsx";;
            6) execute_test "program" "expansion.xlsx";;
            7) execute_test "program" "pwd.xlsx";;
            8) execute_test "program" "redirections.xlsx";;
            9) execute_test "program" "signals.xlsx";;
            10) execute_test "program" "complex_cases.xlsx";;
            0) execute_test "program" "basic_cases.xlsx";;
            f) break ;;
            *) echo -e "${RED}Invalid option.${NC}" ;;
        esac
        
        echo -e "${ORANGE}"
		read -n 1 -rsp "Press any key to return to the menu..." ;
    done
}
