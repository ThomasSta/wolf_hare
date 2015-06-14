#include <iostream>
#include <cstdlib>

const int xSolution = 0;
const int ySolution = 0;
const int xSize = 5;
const int ySize = 5;

struct game {
    	int xwolf1;
	int ywolf1;
	int xwolf2;
	int ywolf2;
	int xhase;
	int yhase;
	game *north;
	game *east;
	game *south;
	game *west;
};


void print(struct game game)
{
	for(int j = 0; j < ySize; j++)
	{
		for(int i = 0; i < xSize; i++)
		{
			if(i == game.xwolf1 && j == game.ywolf1) std::cout << "w ";
			else if(i == game.xwolf2 && j == game.ywolf2) std::cout << "w ";
			else if(i == game.xhase && j == game.yhase) std::cout << "h ";
			else if(i == xSolution && j == ySolution) std::cout << "o ";
			else std::cout << "x ";	
		}
		std::cout << std::endl;
	}
		std::cout << std::endl;

}

void neighborsW1(struct game game)
{

	if(game.xwolf1 > 0)
	{
		struct game west = {(game.xwolf1)-1, game.ywolf1, game.xwolf2, game.ywolf2, game.xhase, game.yhase, NULL, NULL, NULL, NULL};
		game.west = &west;	
	}
	if(game.xwolf1 < xSize-1)
	{
		struct game east = {(game.xwolf1)+1, game.ywolf1, game.xwolf2, game.ywolf2, game.xhase, game.yhase, NULL, NULL, NULL, NULL};
		game.east = &east;
	}
	if(game.ywolf1 > 0)
	{
		struct game south = {game.xwolf1, (game.ywolf1)-1, game.xwolf2, game.ywolf2, game.xhase, game.yhase, NULL, NULL, NULL, NULL};
		game.south = &south;
	}
	if(game.xwolf1 < ySize-1)
	{
		struct game north  = {game.xwolf1, (game.ywolf1)+1, game.xwolf2, game.ywolf2, game.xhase, game.yhase, NULL, NULL, NULL, NULL};
		game.north = &north;
	}

}

void neighborsW2(struct game game)
{

	if(game.xwolf1 > 0)
	{
		struct game west = {game.xwolf1, game.ywolf1, (game.xwolf2)-1, game.ywolf2, game.xhase, game.yhase, NULL, NULL, NULL, NULL};
		game.west = &west;	
	}
	if(game.xwolf1 < xSize-1)
	{
		struct game east = {game.xwolf1, game.ywolf1, (game.xwolf2)+1, game.ywolf2, game.xhase, game.yhase, NULL, NULL, NULL, NULL};
		game.east = &east;
	}
	if(game.ywolf1 > 0)
	{
		struct game south = {game.xwolf1, game.ywolf1, game.xwolf2, (game.ywolf2)-1, game.xhase, game.yhase, NULL, NULL, NULL, NULL};
		game.south = &south;
	}
	if(game.xwolf1 < ySize-1)
	{
		struct game north  = {game.xwolf1, game.ywolf1, game.xwolf2, (game.ywolf2)+1, game.xhase, game.yhase, NULL, NULL, NULL, NULL};
		game.north = &north;
	}

}

void neighborsHasi(struct game game)
{

	if(game.xwolf1 > 0)
	{
		struct game west = {game.xwolf1, game.ywolf1, game.xwolf2, game.ywolf2, (game.xhase)-1, game.yhase, NULL, NULL, NULL, NULL};
		game.west = &west;	
	}
	if(game.xwolf1 < xSize-1)
	{
		struct game east = {game.xwolf1, game.ywolf1, game.xwolf2, game.ywolf2, (game.xhase)+1, game.yhase, NULL, NULL, NULL, NULL};
		game.east = &east;
	}
	if(game.ywolf1 > 0)
	{
		struct game south = {game.xwolf1, game.ywolf1, game.xwolf2, game.ywolf2, game.xhase, (game.yhase)-1, NULL, NULL, NULL, NULL};
		game.south = &south;
	}
	if(game.xwolf1 < ySize-1)
	{
		struct game north  = {game.xwolf1, (game.ywolf1)+1, game.xwolf2, game.ywolf2, game.xhase, (game.yhase)+1, NULL, NULL, NULL, NULL};
		game.north = &north;
	}

}



int main(int argc, char **argv)
{

	game game;
	game.xwolf1 = 1;
	game.ywolf1 = 1;
	game.xwolf2 = 2;
	game.ywolf2 = 2;
	game.xhase = 3;
	game.yhase = 4;

	print(game);
	
	neighborsW1(game);


	print(*game.north);
	print(*game.east);
	print(*game.south);
	print(*game.west);

/*
	if(!test.isSolution()) std::cout << "no solution :("  << std::endl;

	std::cout << std::endl;

	test.init(1,1,3,3,3,3,4,4,5,5);
	test.print();
	if(test.isSolution()) std::cout << "solution :)"  << std::endl;

	Game neighbors[4] = {Game(5,5), Game(5,5), Game(5,5), Game(5,5)};
	for( int i = 0; i < 4; i++)
	{
		neighbors[i] = test;
	}

	int x = test.neighborsW1(&neighbors);

	for( int i = 0; i < x; i++)
	{
		neighbors[i].print();
	}
*/
	return 0;
}
