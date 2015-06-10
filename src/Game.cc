#include <iostream>
#include <cstdlib>

#include "Array.hh"
#include "Game.hh"

//		static const int MAX_NEIGHBORS = 64; // 4*4*4

Game::Game(int sizex, int sizey)
{

	playField_ = new Array(sizex, sizey);
	xw1_ = 0;
	yw1_ = 0;
	xw2_ = 0;
	yw2_ = 0;
	xh_ = 0;
	yh_ = 0;
	xsolution_ = 0;
	ysolution_ = 0;

}

Game::~Game()
{
	delete playField_;
}

void Game::init(int xw1, int yw1, int xw2, int yw2, int xh, int yh, int xsolution, int ysolution)
{

	for (int y = 0; y < playField_->getSize(DIM_2D); y++) {
		for (int x = 0; x < playField_->getSize(DIM_1D); x++)
		{
			playField_->operator()(x,y) = 'O';
		}
	}

	playField_->operator()(xh,yh) = 'H';
	playField_->operator()(xw1,yw1) = 'W';
	playField_->operator()(xw2,yw2) = 'W';
	playField_->operator()(xsolution,ysolution) = 'G';
	
	xw1_ = xw1;
	yw1_ = yw1;
	xw2_ = xw2;
	yw2_ = yw2;
	xh_ = xh;
	yh_ = yh;
	xsolution_ = xsolution;
	ysolution_ = ysolution;

}
/*
   int neighbors(Game *hood) const
   {
   int num = 0;
   if (xw1 > 0) {
   FifteenPuzzle& ref = hood[num];
   ref = *this;
   ++num;
   std::swap(ref.tiles[cY * 4 + cX],
   ref.tiles[cY * 4 + cX - 1]);
   --ref.cX;
   }

   return num;
   }
 */
void Game::print()
{
	for (int y = 0; y < playField_->getSize(DIM_2D); y++) {
		for (int x = 0; x < playField_->getSize(DIM_1D); x++)
		{
			std::cout << playField_->operator()(x,y) << " ";
		}
		std::cout << "\n";
	}
	//	std::cout << "\n";
}


bool Game::isSolution()
{

	if(((xw1_ == xh_) && (yw1_ == yh_)) || ((xw2_ == xh_) && (yw2_ == yh_))) return true;

	return false;

}

/*
   bool operator==(const FifteenPuzzle& other) const
   {
   for (int i = 0; i < 16; ++i)
   if (tiles[i] != other.tiles[i])
   return false;
   return true;
   }

*/
/*
   template<class PUZZLE>
   class DepthSearch
   {
   public:
   bool operator()(const PUZZLE& p, const int& maxDepth)
   {

   if(p.isSolution())
   {
   std::cout << "\nsolved:" << std::endl;
   p.print();
   exit(1);
   }

   if(maxDepth == 0)
   {
   return false;
   }

   PUZZLE neighbors[PUZZLE::MAX_NEIGHBORS];
   int actualNeighbors = p.neighbors(neighbors);

   for(int i = 0; i < actualNeighbors; i++)
   {
   (*this)(neighbors[i], maxDepth - 1);
   }

   }
   };

   template<class PUZZLE>
   class DepthSearchRemember
   {
   public:
   bool operator()(const PUZZLE& p, const int& maxDepth, PUZZLE *used, int index)
   {

   if(p.isSolution())
   {
   std::cout << "\nsolved:" << std::endl;
   p.print();
   exit(1);
   }

   if(maxDepth == 0)
   {
   return false;
   }

   for(int i = 0; i < 50; i++)
   {
   if(p == used[i])
   {
   return false;
   }
   else
   {
   p.setTo(used, index);
   index++;

   std::cout << index << std::endl;
   for(int i = 0; i < 3; i++)
   {
   std::cout << i << std::endl;
   used[i].print();
   }

   if(index == 50) index = 0;
   break;
   }
}
//std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

PUZZLE neighbors[PUZZLE::MAX_NEIGHBORS];
int actualNeighbors = p.neighbors(neighbors);

for(int i = 0; i < actualNeighbors; i++)
{
	(*this)(neighbors[i], maxDepth - 1, used, index);
}

}
};
*/
