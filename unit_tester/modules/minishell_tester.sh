#!/usr/bin/env bash

minishell_tester_menu() {
	echo "Running Minishell tests..."
    while true; do
        clear
        echo -e "${BLUE}----- Minishell Tester -----${NC}"
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
            1) run_echo_cases ;;
            2) run_dollar_expansion_cases ;;
            3) run_quotation_cases ;;
			4) run_piping_cases ;;
			5) run_redirection_cases ;;
			6) run_and_or_cases ;;
			7) run_wildcard_cases ;;
			8) run_export_env_cases ;;
			9) run_exit_status_handling_cases ;;
			10) run_signals_handling_cases ;;
			11) run_mix_complex_cases ;;
            0) break ;;
            *) echo "Invalid option." ;;
        esac
    done
}
