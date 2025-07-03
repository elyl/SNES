NAME=	snes_decompiler
SRC=	main.c
OBJ=	$(SRC:.c=.o)
CC=		gcc
CFLAGS=	-W -Wall
RM=		@rm -fv

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(NAME)

re: clean fclean $(NAME)
