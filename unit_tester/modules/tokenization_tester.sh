#!/usr/bin/env bash

run_tokenization_tests() {
	test_case="tokenization"
	dir="test_files/$test_case"

	while true; do
		clear
		echo -e "${BLUE}----- Tokenization Tester -----${NC}"
		echo -e "${GREEN}a) ${CYAN}Run All Cases"
		echo -e "${GREEN}1) Echo & \$ & Quotation Cases"
		echo -e "2) Piping"
		echo -e "3) Redirections"
		echo -e "4) AND (&&) / OR (||)"
		echo -e "5) Wildcard"
		echo -e "6) Export / Env"
		echo -e "7) Exit Status Handling"
		echo -e "8) Signals Handling"
		echo -e "9) Mix / Complex Cases${NC}"
		echo -e "${ORANGE}f) Return to Tokenization Menu${GREEN}"
		echo -e
		read -n 1 -rp "Select an option: " choice

		case $choice in
			a) echo -n
				run_all_cases "tokenization"
      	 		continue ;;
			1) file="$dir/tokenization_echo.xlsx" ;;
			2) file="$dir/tokenization_piping.xlsx" ;;
			3) file="$dir/tokenization_redirections.xlsx" ;;
			4) file="$dir/tokenization_and_or.xlsx" ;;
			5) file="$dir/tokenization_wildcard.xlsx" ;;
			6) file="$dir/tokenization_export_env.xlsx" ;;
			7) file="$dir/tokenization_exit_status.xlsx" ;;
			8) file="$dir/tokenization_signals.xlsx" ;;
			9) file="$dir/tokenization_complex_cases.xlsx" ;;
			f) break ;;
			*) echo "Invalid option." ; 
				continue ;;
		esac

		run_test_case "$file"

		echo -e
		read -n 1 -rsp "Press any key to continue..." ;
	done
}

tokenization_tester_menu() {
	while true; do
		clear
		echo -e "${BLUE}----- Tokenization Tester -----${NC}"
		echo -e "${GREEN}a) ${CYAN}Run All Cases (old version)"
		echo -e "${GREEN}1) Run partial tests"
		echo -e "2) Set tokenization file path"
		echo -e "3) Set token struct header path${NC}"
		echo -e "${ORANGE}f) Return to Main Menu${GREEN}"
		echo -e
		read -n 1 -rp "Select an Option: " choice
		
		case $choice in
			a) run_all_tokenization_cases ;; 
			1) run_tokenization_tests ;; 
			2) read -rp "Enter tokenization file path: " TOKEN_FILE ;;
			3) read -rp "Enter struct header path: " TOKEN_STRUCT ;;
			f) break ;;
			*) echo "Invalid option." ;;
		esac
	done
}
