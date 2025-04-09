#!/usr/bin/env bash

###############################################################################
# display_failed_summary()
#
#   This function parses the FAILED_SUMMARY_FILE and displays the failed
#   test cases according to the provided argument.
#
#   If the argument is "all", it prints all failure summaries grouped
#   by header. If the argument is a specific test type (e.g. "program" or
#   "tokenization"), it prints only the failures that belong to that test type.
#
# Usage:
#   display_failed_summary "all"
#   display_failed_summary "program"
###############################################################################

display_failed_summary() {
  local filter="$1"
  
  if [[ ! -s "$FAILED_SUMMARY_FILE" ]]; then
    echo -e "${GREEN}No failed test cases to report.${RESET}"
    return 0
  fi

  if [[ "$filter" == "all" ]]; then
    echo -e "${BLUE}Summary of All Failed Test Cases:${RESET}"
    awk '
      BEGIN { block_line = 0; }
      # A header is any line that begins with "Test type:"
      /^Test type:/ {
        # If we already printed a block, insert a separator
        if (block_line > 0) { print "\n----------------------\n"; }
        block_line = 0;
        # Print header (first line) in blue:
        printf "\033[34m%s\033[0m\n", $0;
        block_line++;
        next;
      }
      {
        if (block_line == 1) {
          # Second line: print in green.
          printf "\033[32m%s\033[0m\n", $0;
        } else if (block_line == 2) {
          # Third line: print in red.
          printf "\033[31m%s\033[0m\n", $0;
        } else {
          # Subsequent lines: no special color.
          print $0;
        }
        block_line++;
      }
    ' "$FAILED_SUMMARY_FILE"
  else
    echo -e "${BLUE}Summary of Failed Test Cases for $filter:${RESET}"
    # We assume the header in the summary file is of the form:
    #   Test type: <filter>
    awk -v hdr="Test type: $filter" '
      BEGIN { print_block = 0; block_line = 0; }
      # When we see a matching header, enable printing
      $0 == hdr {
        print_block = 1;
        block_line = 0;
        printf "\033[34m%s\033[0m\n", $0;
        block_line++;
        next;
      }
      # When we see any header that is not the target, disable printing.
      /^Test type:/ { print_block = 0; }
      print_block {
        if (block_line == 1) {
          printf "\033[32m%s\033[0m\n", $0;
        } else if (block_line == 2) {
          printf "\033[31m%s\033[0m\n", $0;
        } else {
          print $0;
        }
        block_line++;
      }
    ' "$FAILED_SUMMARY_FILE"
  fi
}