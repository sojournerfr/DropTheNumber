##
## EPITECH PROJECT, 2024
## Amazed
## File description:
## Makefile
##

SRC		=	src/main.c \
			src/utils/handle_matrix.c \
			src/utils/handle_game.c

BIN_NAME	=	DropTheNumber

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Wall -Wextra -lm

all: $(BIN_NAME)

$(BIN_NAME): $(OBJ)
	@gcc -o $(BIN_NAME) $(OBJ) $(CFLAGS)
	@echo "[OK] Binary '$(BIN_NAME)' compiled successfully."

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -f $(OBJ)
	@echo "[INFO] Object files removed."

fclean: clean
	@rm -f $(BIN_NAME)
	@echo "[INFO] Binary '$(BIN_NAME)' removed."

re: fclean all
	@echo "[INFO] Project rebuilt successfully."
