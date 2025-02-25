#!/usr/bin/env bash

# Load external scripts
source ./modules/minishell_tester.sh
source ./modules/tokenization_tester.sh
source ./modules/settings_menu.sh
source ./modules/excel_parser.sh
source ./modules/valgrind_tester.sh
source ./modules/test_execution.sh

# Load Configuration
CONFIG_FILE="./tester_config.ini"
if [[ ! -f "$CONFIG_FILE" ]]; then
    echo "COMPARISON_METHOD=csv" > "$CONFIG_FILE"
    echo "VALGRIND_ENABLED=0" >> "$CONFIG_FILE"
    echo "EXCEL_FILE=tests.xlsx" >> "$CONFIG_FILE"
    echo "CSV_FILE=tests.csv" >> "$CONFIG_FILE"
fi
source "$CONFIG_FILE"

# Color Codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
CYAN='\033[1;36m'
NC='\033[0m' # No Color

# Main Menu
while true; do
    clear
    echo -e "${BLUE}----- Minishell Tester -----${NC}"
    echo -e "${GREEN}1) Minishell Tester${NC}"
    echo -e "${GREEN}2) Tokenization Tester${NC}"
    echo -e "${GREEN}3) Parsing Tester${NC}"
    echo -e "${GREEN}4) Settings${NC}"
    echo -e "${RED}0) Exit${NC}"
    read -rp "Select an option: " choice
    case $choice in
        1) minishell_tester_menu ;;
        2) tokenization_tester_menu ;;
        3) echo "Running Parsing tests...";;
        4) settings_menu;;
        0) clear ; exit 0;;
        *) echo -e "${RED}Invalid option.${NC}";;
    esac
done
