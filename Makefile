# Name of the executable
NAME = shello
# Directories
OBJ_DIR = obj
# Libraries and compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBS = -lGL -lGLU -lglut
RM = rm -f
# Source and object files
SRC_FILES = main shell_interactive shell_no_interactive builtin
SRC = $(addsuffix .c, $(addprefix src/, $(SRC_FILES)))
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
# Include directories
INCLUDES = -Iinclude
# Default target
all: setup $(OBJ_DIR) $(NAME)
# Compiling object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
# Linking the executable
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo "Linking the executable..."
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "$(NAME) is ready."
# Create the object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
# Clean object files
clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "Object files cleaned."
# Clean object files and executable
fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) and related files cleaned."
# Rebuild everything
re: fclean all
.PHONY: all clean fclean re setup
