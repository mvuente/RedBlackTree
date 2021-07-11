NAME = tree
SRC = main.cpp Tree.cpp
OBJ = $(SRC:.cpp=.o)
HEAD = Tree.hpp
all: $(NAME)
$(NAME): $(OBJ)
	clang++ $(OBJ) -o $(NAME)

%.o: %.cpp $(HEAD)
	clang++ -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
