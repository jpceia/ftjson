NAME        = libjson.a

INC_DIR     = headers

SRC_DIR     = src
TEST_DIR    = test_src
OBJ_DIR     = obj
BIN_DIR     = bin

SRCS        = $(shell find $(SRC_DIR) -name "*.c" -type f)
SRCS_TEST   = $(shell find $(TEST_DIR) -name "*.c" -type f)
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_TEST   = $(SRCS_TEST:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

CC          = gcc
RM          = rm -f

OS          = $(shell uname)

FLAGS_WARN  = -Wall -Wextra -Werror
FLAGS_INC   = -I$(INC_DIR)
FLAGS_DEBUG = -ggdb3 -DDEBUG -fsanitize=address
FLAGS_OPT   = -O3
TESTER_LIBS = -ljson -lcheck -lz -lrt -pthread -lm -lsubunit

CFLAGS      = $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_INC)
LDFLAGS     = $(FLAGS_WARN) $(FLAGS_OPT) -L./$(BIN_DIR)

all:        $(NAME)

# Compilation
$(OBJ_DIR)/%.o:  $(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o:  $(TEST_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) -c $< -o $@ $(CFLAGS)

# Linking
$(NAME):    $(OBJS)
			ar rcs $(NAME) $^
			ranlib $(NAME)
			@mkdir -p $(BIN_DIR)
			mv $(NAME) $(BIN_DIR)

# Tester
test:		$(NAME) $(OBJS_TEST)
			$(CC) $(OBJS_TEST) -o $@ $(LDFLAGS) $(TESTER_LIBS) $(FLAGS_DEBUG)
			./$@
			$(RM) $@

# Cleaning
clean:
			$(RM) -rf $(OBJ_DIR)

fclean:     clean
			$(RM) -rf $(BIN_DIR)

# Debugging build
debug:      CFLAGS += $(FLAGS_DEBUG)
debug:      LDFLAGS += $(FLAGS_DEBUG)
debug:      re

# Rebuid
re:         fclean all

.PHONY:     all clean fclean re debug
