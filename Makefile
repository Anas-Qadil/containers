

NAME	= exe
SRC		= main.cpp
OBJ		= main.o
HEADER	= ./map/RBTree.hpp ./map/pair.hpp ./map/map.hpp
CC		= c++

$(NAME)	: $(OBJ) $(HEADER)
	$(CC) $(SRC) -o $(NAME)

all		: $(NAME)
	

%.o	: %.cpp $(HEADER) 
	$(CC) -c $<

clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re		: fclean all


