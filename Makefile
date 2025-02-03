NAME = ircserv

OBJ_DIR =	obj
SOURCES =	main.cpp

MAKE_DIR = mkdir -p
SRC = $(SOURCES)
OBJ = $(SRC:.cpp=.o)
OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ))

INCLUDES := -I includes
CPPC = c++
CPPVERSION = -std=c++98
CPPFLAGS = -Wall -Wextra -Werror -g3 $(CPPVERSION) -fsanitize=address -g3

all: c_dir $(NAME)

$(NAME): $(OBJ)
	$(CPPC) $(CPPFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CPPC) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

c_dir:
	$(MAKE_DIR) $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f *_shrubbery

re: fclean all

.PHONY : all clean fclean re