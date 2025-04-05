#!/usr/bin/env bash

# add option to toggle running all tests within the same instance or exit after each test

# update_config_key KEY VALUE FILE
# Replaces KEY=... line in FILE if it exists, or appends if it doesn't
update_config_key() {
    local key="$1"
    local value="$2"
    local file="$3"

    if grep -q "^$key=" "$file"; then
        # Replace existing line
        sed -i "s|^$key=.*|$key=$value|" "$file"
    else
        # Append the key/value
        echo "$key=$value" >> "$file"
    fi
}

# Settings Menu
settings_menu() {
    while true; do
        clear
        echo -e "${BLUE}----- Settings -----${NC}"
        echo -e "${GREEN}1) Set Excel file for test cases (Current: $EXCEL_FILE)${NC}"
        echo -e "${GREEN}2) Toggle Valgrind usage (Current: $VALGRIND_ENABLED)${NC}"
        echo -e "${GREEN}3) Toggle comparison method (Current: $COMPARISON_METHOD)${NC}"
        echo -e "${GREEN}4) Toggle bonus testing (Current: $BONUS_TESTING_ENABLED)${NC}"
        echo -e "${GREEN}5) Set Program Prompt (Current: '$PROGRAM_PROMPT')${NC}"
        echo -e "${ORANGE}f) Return to Main Menu${NC}"
        echo -e
        read -rp "Select an option: " choice
        case $choice in
            1)
                read -rp "Enter path to Excel file: " EXCEL_FILE
                update_config_key "EXCEL_FILE" "$EXCEL_FILE" "$CONFIG_FILE"
                ;;
            2)
                VALGRIND_ENABLED=$((1 - VALGRIND_ENABLED))
                update_config_key "VALGRIND_ENABLED" "$VALGRIND_ENABLED" "$CONFIG_FILE"
                ;;
            3)
                COMPARISON_METHOD=$([[ "$COMPARISON_METHOD" == "csv" ]] && echo "bash" || echo "csv")
                update_config_key "COMPARISON_METHOD" "$COMPARISON_METHOD" "$CONFIG_FILE"
                ;;
            4)
                BONUS_TESTING_ENABLED=$((1 - BONUS_TESTING_ENABLED))
                update_config_key "BONUS_TESTING_ENABLED" "$BONUS_TESTING_ENABLED" "$CONFIG_FILE"
                ;;
            5)
                read -rp "Enter new Program Prompt (e.g. Minishell>): " PROGRAM_PROMPT
                update_config_key "PROGRAM_PROMPT" "$PROGRAM_PROMPT" "$CONFIG_FILE"
                ;;
            f) break ;;
            *) echo -e "${RED}Invalid option.${NC}" ;;
        esac
    done
}
