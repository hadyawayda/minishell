#!/usr/bin/env bash

# Convert Excel to CSV
convert_excel_to_csv() {
	clear
	local excel_file="$1"
    local csv_file="${excel_file%.xlsx}.csv"

    echo -e "${CYAN}Converting Excel file to CSV...${NC}"

    # Check if the Excel file exists
    if [[ ! -f "$excel_file" ]]; then
        echo -e "${RED}Error: Excel file '$excel_file' not found.${NC}"
        return 1
    fi

    # Convert Excel to CSV
    if command -v xlsx2csv &> /dev/null; then
        xlsx2csv "$excel_file" > "$csv_file"
    elif command -v ssconvert &> /dev/null; then
        ssconvert "$excel_file" "$csv_file"
    else
        echo -e "${RED}Error: No Excel to CSV conversion tool found.${NC}"
        return 1
    fi

    # Check if CSV file was successfully created
    if [[ ! -f "$csv_file" ]]; then
        echo -e "${RED}Error: CSV file '$csv_file' was not created.${NC}"
        return 1
    fi

    echo -e "${GREEN}Conversion complete.${NC}"
    return 0
}
