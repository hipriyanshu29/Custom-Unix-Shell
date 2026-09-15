TARGET=my_shell
OBJ=main.c input_parser.c helper_functions.c builtin.c executor.c
CC=gcc

all:
	$(CC)  -o $(TARGET) $(OBJ)
clean:
	rm -f *-o
fclean:
	rm -f $(TARGET)
re: fclean all
