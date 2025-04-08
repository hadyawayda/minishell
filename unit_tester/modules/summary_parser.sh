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
    echo -e "${GREEN}No failed test cases to report.$"
    return 0
  fi

  if [[ "$filter" == "all" ]]; then
    echo -e "${YELLOW}Summary of All Failed Test Cases:$"
    # Use awk to group failures by header. Every header line is assumed
    # to start with "Test type:".
    awk '
      BEGIN { group = ""; }
      /^Test type:/ {
         if (group != "") { print "\n----------------------\n"; }
         group = $0;
         print $0;
         next;
      }
      { print; }
    ' "$FAILED_SUMMARY_FILE"
  else
    echo -e "${BLUE}Summary of Failed Test Cases for $filter cases:\\n${RED}"
    # Use awk to search for the header matching the given test type
    # and print all lines until the next header.
    awk -v header="Test type: $filter" '
      $0 == header { print; inblock = 1; next }
      /^Test type:/ { inblock = 0 }
      inblock { print; }
    ' "$FAILED_SUMMARY_FILE"
  fi
  echo -e "${GREEN}"
  read -n 1 -rp "Press any key to continue..."
}
