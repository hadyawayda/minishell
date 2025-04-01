#!/usr/bin/env bash

# Load external scripts
source ./modules/csv_parser.sh
source ./modules/minishell_tester.sh
source ./modules/parsing_tester.sh
source ./modules/settings_menu.sh
source ./modules/test_execution.sh
source ./modules/tokenization_tester_script.sh
source ./modules/tokenization_tester.sh
source ./modules/valgrind_tester.sh

# Load Configuration
CONFIG_FILE="./config/tester_config.ini"
if [[ ! -f "$CONFIG_FILE" ]]; then
    echo "COMPARISON_METHOD=csv" > "$CONFIG_FILE"
    echo "VALGRIND_ENABLED=0" >> "$CONFIG_FILE"
    echo "EXCEL_FILE=tests.xlsx" >> "$CONFIG_FILE"
    echo "CSV_FILE=tests.csv" >> "$CONFIG_FILE"
    echo "BONUS_TESTING_ENABLED=0" >> "$CONFIG_FILE"
fi
source "$CONFIG_FILE"

# Color Codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
ORANGE='\033[38;5;208m'
BLUE='\033[1;34m'
CYAN='\033[1;36m'
NC='\033[0m'
# Uncomment the following line to enable flashy colors
RED='\033[1;31m'
GREEN="\033[1;32m"

clear
echo -e "${CYAN}Welcome to the Minishell Tester!${NC}"
echo -e "${GREEN}This script will help you test your Minishell implementation.${NC}"
echo -e "${GREEN}Please ensure you have the necessary test files in the correct format (refer to the README file for details).${NC}"
echo -e "${GREEN}Press any key to continue...${NC}"
read -n 1 -s
echo -e "${GREEN}Starting the tester...${NC}"

# Main Menu
while true; do
    clear
    echo -e "${BLUE}----- Minishell Tester -----${NC}"
    echo -e "${GREEN}1) Minishell Tester${NC}"
    echo -e "${GREEN}2) Tokenization Tester${NC}"
    echo -e "${GREEN}3) Parsing & Tree Tester (Upcoming Feature)${NC}"
    echo -e "${GREEN}4) Settings (Upcoming Feature)${NC}"
    echo -e "${ORANGE}f) Exit${GREEN}"
    echo -e
    read -rp "Select an option: " choice
    case $choice in
        1) minishell_tester_menu ;;
        2) tokenization_tester_menu ;;
        3) parsing_tester_menu ;;
        4) settings_menu;;
        f) clear ; exit 0;;
        *) echo -e "${RED}Invalid option.${NC}";;
    esac
done
