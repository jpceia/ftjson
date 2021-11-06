NAME        = cjson

INC_DIR     = headers

SRC_DIR     = src
OBJ_DIR     = obj

SRCS        = $(shell find $(SRC_DIR) -name "*.c" -type f)
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC          = gcc
RM          = rm -f

OS          = $(shell uname)

FLAGS_WARN  = -Wall -Wextra -Werror
FLAGS_INC   = -I$(INC_DIR)
FLAGS_DEBUG = -ggdb3 -fsanitize=address -DDEBUG
FLAGS_OPT   = 

CFLAGS      = $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_INC) 
LDFLAGS      = $(FLAGS_WARN) $(FLAGS_OPT) -lasan

all:        $(NAME)

# Compilation
$(OBJ_DIR)/%.o:  $(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) -c $< -o $@ $(CFLAGS)

# Linking
$(NAME):    $(OBJS)
			$(CC) $^ -o $@ $(LDFLAGS)

# Cleaning
clean:
			$(RM) -r $(OBJ_DIR)

fclean:     clean
			$(RM) $(NAME) checker

# Debugging build
debug:      CFLAGS += $(FLAGS_DEBUG)
debug:      LDFLAGS += $(FLAGS_DEBUG)
debug:      re

# Rebuid
re:         fclean all

.PHONY:     all clean fclean re debug
