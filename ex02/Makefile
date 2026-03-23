NAME = PmergeMe

CC = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror
LDFLAGS = 

SRC = main.cpp PmergeMe.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CXXFLAGS) -o $(NAME) $(LDFLAGS)
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
