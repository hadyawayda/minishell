make re

valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --suppressions=valgrind.supp ./michel

make fclean