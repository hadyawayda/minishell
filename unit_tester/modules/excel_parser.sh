#!/usr/bin/env bash

# Convert Excel to CSV
convert_excel_to_csv() {
    echo -e "${CYAN}Converting Excel file to CSV...${NC}"
    if command -v ssconvert &> /dev/null; then
        ssconvert "$EXCEL_FILE" "$CSV_FILE"
    elif command -v xlsx2csv &> /dev/null; then
        xlsx2csv "$EXCEL_FILE" > "$CSV_FILE"
    else
        echo -e "${RED}Error: No Excel to CSV conversion tool found.${NC}"
        exit 1
    fi
    echo -e "${GREEN}Conversion complete.${NC}"
}