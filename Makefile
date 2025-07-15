NAME = ircserv

OBJ_DIR =	obj
INC_DIR =	includes
SERVER_FOLDER = Server
UTILS_FOLDER = Utils

SERVER_FILES =  Server \
				init_server \
				init_commands \
				server_listen_loop \
				server_accept \
				server_read \
				parse_message \
				connection_messages \
				register_clients \
				channel_operations \
				messages

UTILS_FILES = str_toupper

SERVER_FILES := $(addprefix $(SERVER_FOLDER)/, $(SERVER_FILES))
UTILS_FILES := $(addprefix $(UTILS_FOLDER)/, $(UTILS_FILES))

SOURCES =	main \
			$(SERVER_FILES) \
			$(UTILS_FILES) \
			Client \
			Channel


INCLUDES =	Server \
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

ifeq ($(tmout),)
else
	CPPFLAGS += -D TIMEOUT=$(tmout)
endif

all: $(NAME)

$(NAME): $(INC) $(OBJ_DIR) $(OBJ)
	$(CPP) $(CPPFLAGS) $(INCLUDE) $(OBJ) -o $@

$(OBJ_DIR)/%.o: src/%.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	$(MAKE_DIR) $(OBJ_DIR)/$(SERVER_FOLDER)
	$(MAKE_DIR) $(OBJ_DIR)/$(UTILS_FOLDER)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
