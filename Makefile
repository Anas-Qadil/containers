

NAME	= exe
SRC		= main.cpp
OBJ		= main.o
HEADER	= ./map/RBTree.hpp
CC		= c++

$(NAME)	: $(OBJ) $(HEADER)
	$(CC) $(SRC) -o $(NAME)

all		: $(NAME)
	

%.o	: %.cpp
	$(CC) -c $<

clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re		: fclean all