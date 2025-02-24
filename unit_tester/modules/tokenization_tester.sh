#!/usr/bin/env bash

tokenization_tester_menu() {
	echo "Running Tokenization tests..."
    while true; do
        clear
        echo -e "${BLUE}----- Tokenization Tester -----${NC}"
        echo -e "${GREEN}1) Set tokenization file path"
        echo -e "2) Set token struct header path"
        echo -e "3) Run tokenization tests${NC}"
        echo -e "${RED}0) Return to Main Menu${NC}"
        
        read -rp "Option: " choice
        
        case $choice in
            1) read -rp "Enter tokenization file path: " TOKEN_FILE ;;
            2) read -rp "Enter struct header path: " TOKEN_STRUCT ;;
            3) run_tokenization_tests ;; 
            0) break ;;
            *) echo "Invalid option." ;;
        esac
    done
}