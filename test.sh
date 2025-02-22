make te

./minishell_test 'echo $USER"a"'
# valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --suppressions=utils/valgrind.supp ./minishell_test 'echo $USER"a"'


make tclean
