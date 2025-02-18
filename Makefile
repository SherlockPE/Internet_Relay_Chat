NAME = ircserv

OBJ_DIR =	obj
INC_DIR =	includes

SOURCES =	main.cpp \
			Server.cpp

INCLUDES = Server.hpp

MAKE_DIR = mkdir -p

SRC = $(SOURCES)
OBJ = $(SRC:.cpp=.o)
OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ))

INC = $(addprefix $(INC_DIR)/, $(INCLUDES))

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