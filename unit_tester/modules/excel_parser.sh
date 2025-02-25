#!/usr/bin/env bash
#
# Usage:
#   ./convert_excel_to_two_columns_delimited.sh /path/to/file.xlsx
#
# Description:
#   1. Extracts only column 1 of the spreadsheet into _input.csv.
#   2. Extracts only column 2 of the spreadsheet into _output.csv.
#   3. Appends `ǂ` after each row, ensuring multi-line fields remain intact.

convert_excel_to_csv() {
    if [ $# -lt 1 ]; then
        echo "Usage: $0 /path/to/file.xlsx"
        exit 1
    fi
    
    local input_file="$1"
    local base_name
    base_name=$(basename "$input_file" .xlsx)
    
    # Define custom delimiter
    local delimiter="ǂ"  # Change this if needed
    
    # Extract to temporary regular CSVs first
    in2csv "$input_file" | csvcut -c 1 > "${base_name}_temp1.csv"
    in2csv "$input_file" | csvcut -c 2 > "${base_name}_temp2.csv"
    
    # Use Python to properly handle the CSV structure and add delimiters
    python3 -c "
import csv
import sys

# Process column 1
with open('${base_name}_temp1.csv', 'r', newline='') as infile, open('${base_name}_input.csv', 'w') as outfile:
    reader = csv.reader(infile)
    for row in reader:
        value = row[0] if row else ''
        outfile.write(value + '${delimiter}' + '\n')

# Process column 2
with open('${base_name}_temp2.csv', 'r', newline='') as infile, open('${base_name}_output.csv', 'w') as outfile:
    reader = csv.reader(infile)
    for row in reader:
        value = row[0] if row else ''
        outfile.write(value + '${delimiter}' + '\n')
    " 
    
    # Clean up temporary files
    rm "${base_name}_temp1.csv" "${base_name}_temp2.csv"
    
    echo "Done."
    echo "  - ${base_name}_input.csv (column 1, rows delimited with '$delimiter')"
    echo "  - ${base_name}_output.csv (column 2, rows delimited with '$delimiter')"
}

# If the script is executed directly (not sourced), run the function with all args.
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    convert_excel_to_csv "$@"
fi