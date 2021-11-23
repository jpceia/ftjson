NAME            = libjson.a

INC_DIR         = headers

SRC_DIR         = src
TEST_SRC_DIR    = test_src
OBJ_DIR         = obj
TEST_OBJ_DIR    = test_obj
BIN_DIR         = bin

SRCS        = $(shell find $(SRC_DIR) -name "*.c" -type f)
TEST_SRCS   = $(shell find $(TEST_SRC_DIR) -name "*.c" -type f)
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJS   = $(TEST_SRCS:$(TEST_SRC_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)

CC          = gcc
RM          = rm -f

OS          = $(shell uname)

FLAGS_WARN  = -Wall -Wextra -Werror -pedantic-errors
FLAGS_INC   = -I$(INC_DIR)
FLAGS_DEBUG = -ggdb3 -DDEBUG -fsanitize=address
FLAGS_OPT   = -O3
TESTER_LIBS = -ljson -lcheck -lz -lrt -pthread -lm -lsubunit

CFLAGS      = $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_INC)
LDFLAGS     = $(FLAGS_WARN) $(FLAGS_OPT) -L$(BIN_DIR)

all:        $(NAME)

# Compilation
$(OBJ_DIR)/%.o:  $(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) -c $< -o $@ $(CFLAGS)

$(TEST_OBJ_DIR)/%.o:  $(TEST_SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) -c $< -o $@ $(CFLAGS)

# Linking
$(NAME):    $(OBJS)
			ar rcs $(NAME) $^
			ranlib $(NAME)
			@mkdir -p $(BIN_DIR)
			mv $(NAME) $(BIN_DIR)

# Tester
test:		$(NAME) $(TEST_OBJS)
			$(CC) $(TEST_OBJS) -o $@ $(LDFLAGS) $(TESTER_LIBS) $(FLAGS_DEBUG)
			@./$@
			@$(RM) $@

# Cleaning
clean:
			$(RM) -rf $(OBJ_DIR) $(TEST_OBJ_DIR)

fclean:     clean
			$(RM) -rf $(BIN_DIR)

# Debugging build
debug:      CFLAGS += $(FLAGS_DEBUG)
debug:      LDFLAGS += $(FLAGS_DEBUG)
debug:      re

# Rebuid
re:         fclean all

.PHONY:     all clean fclean re debug
