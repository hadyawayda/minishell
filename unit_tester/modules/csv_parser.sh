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
    local input_file="$1"
    local base_name=$(basename "$input_file" .xlsx)

    local delimiter="ǂ"
    
	mkdir -p "$CONVERTED_FILES_DIR" || { echo "Failed to create $CONVERTED_FILES_DIR"; return 1; }

	rm -f "$CONVERTED_FILES_DIR/${base_name}_input.csv" \
          "$CONVERTED_FILES_DIR/${base_name}_output.csv" \
          "$CONVERTED_FILES_DIR/${base_name}_expected_input.csv" \
          "$CONVERTED_FILES_DIR/${base_name}_expected_output.csv"
    
    in2csv "$input_file" | csvcut -c 1 > "$CONVERTED_FILES_DIR/${base_name}_expected_input.csv"
    in2csv "$input_file" | csvcut -c 2 > "$CONVERTED_FILES_DIR/${base_name}_expected_output.csv"

    python3 - <<EOF
import csv
base_dir = "$CONVERTED_FILES_DIR"
delimiter = "$delimiter"
base_name = "$base_name"

with open(f"{base_dir}/{base_name}_expected_input.csv") as infile, open(f"{base_dir}/{base_name}_input.csv", "w") as outfile:
    for row in csv.reader(infile):
        outfile.write((row[0] if row else "") + delimiter + "\n")

with open(f"{base_dir}/{base_name}_expected_output.csv") as infile, open(f"{base_dir}/{base_name}_output.csv", "w") as outfile:
    for row in csv.reader(infile):
        outfile.write((row[0] if row else "") + delimiter + "\n")
EOF

    rm "$CONVERTED_FILES_DIR/${base_name}_expected_input.csv" "$CONVERTED_FILES_DIR/${base_name}_expected_output.csv"
}
