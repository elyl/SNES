NAME=	snes_emulator
SRC=	main.c	\
	ram.c	\
	cpu.c
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
