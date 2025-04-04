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
		return 1
	fi

	# Check if CSV files exist before proceeding
	if [[ ! -f "$input_csv" || ! -f "$output_csv" ]]; then
		echo -e "${RED}Error: CSV files '$input_csv' or '$output_csv' do not exist after conversion.${ORANGE}"
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
	local test_dir="test_files"
	local files=("$test_dir"/tokenization/tokenization_*.xlsx)

	if [[ ${#files[@]} -eq 0 ]]; then
		echo -e "${RED}No tokenization test files found in '$test_dir'.${NC}"
		read -rsp "Press any key to continue..." ; echo
		return
	fi

	for file in "${files[@]}"; do
		echo -e "${BLUE}Running test case:${NC} $file"
		run_test_case "$file"

		echo -e
		read -rsp "Press any key to continue to next case..." ; echo
	done
}

run_tokenization_tests() {
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
		read -rp "Select an option: " choice

		case $choice in
			a) echo -e "${BLUE}Running all test cases...${GREEN}"
				 run_all_cases
      	 continue ;;
			1) file="test_files/tokenization/tokenization_echo.xlsx" ;;
			2) file="test_files/tokenization/tokenization_piping.xlsx" ;;
			3) file="test_files/tokenization/tokenization_redirections.xlsx" ;;
			4) file="test_files/tokenization/tokenization_and_or.xlsx" ;;
			5) file="test_files/tokenization/tokenization_wildcard.xlsx" ;;
			6) file="test_files/tokenization/tokenization_export_env.xlsx" ;;
			7) file="test_files/tokenization/tokenization_exit_status.xlsx" ;;
			8) file="test_files/tokenization/tokenization_signals.xlsx" ;;
			9) file="test_files/tokenization/tokenization_complex_cases.xlsx" ;;
			f) break ;;
			*) echo "Invalid option." ; continue ;;
		esac

		run_test_case "$file"

		echo -e
		read -rsp "Press any key to continue..." ;
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
		read -rp "Option: " choice
		
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
