#!/usr/bin/env bash

sed -i 's/\r$//' minishell-tester/tester.sh

cd minishell-tester
exec ./tester.sh "$@"
