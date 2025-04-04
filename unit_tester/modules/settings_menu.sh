#!/usr/bin/env bash

# add option to toggle running all tests within the same instance or exit after each test

# Settings Menu
settings_menu() {
    clear
	echo "Upcoming feature!"
    echo -e
    read -rp "Press any key to continue..." ;
    return 0
    
    while true; do
        clear
        echo -e "${BLUE}----- Settings -----${NC}"
        echo -e "${GREEN}1) Set Excel file for test cases${NC}"
        echo -e "${GREEN}2) Toggle Valgrind usage (Current: $VALGRIND_ENABLED)${NC}"
        echo -e "${GREEN}3) Toggle comparison method (Current: $COMPARISON_METHOD)${NC}"
        echo -e "${GREEN}4) Toggle bonus testing (Current: $BONUS_TESTING_ENABLED)${NC}"
        echo -e "${ORANGE}f) Return to Main Menu${GREEN}"
        echo -e
        read -rp "Select an option: " choice
        case $choice in
            1) read -rp "Enter path to Excel file: " EXCEL_FILE; echo "EXCEL_FILE=$EXCEL_FILE" > "$CONFIG_FILE";;
            2) VALGRIND_ENABLED=$((1 - VALGRIND_ENABLED)); echo "VALGRIND_ENABLED=$VALGRIND_ENABLED" >> "$CONFIG_FILE";;
            3) COMPARISON_METHOD=$([[ "$COMPARISON_METHOD" == "csv" ]] && echo "bash" || echo "csv"); echo "COMPARISON_METHOD=$COMPARISON_METHOD" >> "$CONFIG_FILE";;
            4) BONUS_TESTING_ENABLED=$((1 - BONUS_TESTING_ENABLED)); echo "BONUS_TESTING_ENABLED=$BONUS_TESTING_ENABLED" >> "$CONFIG_FILE";;
            f) break;;
            *) echo -e "${RED}Invalid option.${NC}";;
        esac
    done
}
