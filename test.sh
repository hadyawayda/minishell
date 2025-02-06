make re

valgrind --leak-check=full --show-leak-kinds=all ./minishell

make fclean