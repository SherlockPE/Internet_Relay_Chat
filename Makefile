NAME = ircserv

OBJ_DIR =	obj
INC_DIR =	includes

SOURCES =	main \
			Server \
			Channel \
			Client

INCLUDES =	Server \
			Channel \
			Client

MAKE_DIR = mkdir -p

SRC = $(addsuffix .cpp, $(SOURCES))

OBJ = $(SRC:.cpp=.o)
OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ))

INC = $(addsuffix .hpp, $(INCLUDES))
INC := $(addprefix $(INC_DIR)/, $(INC))

INCLUDE := -I includes
CPP = c++
CPPVER = -std=c++98
CPPFLAGS = -Wall -Wextra -Werror $(CPPVER) -g3

all: $(NAME)

$(NAME): $(INC) $(OBJ_DIR) $(OBJ)
	$(CPP) $(CPPFLAGS) $(INCLUDE) $(OBJ) -o $@

$(OBJ_DIR)/%.o: src/%.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	$(MAKE_DIR) $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re