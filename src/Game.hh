#include <iostream>
#include <cstdlib>

#include "Array.hh"

class Game
{
	public:
		static const int MAX_NEIGHBORS = 64; // 4*4*4

		Game(int sizex, int sizey);
		~Game();
		
		void init(int xw1, int yw1, int xw2, int yw2, int xh, int yh, int xsolution, int ysolution);
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
		void print();
		bool isSolution();

	private:
		Array *playField_;
		int xw1_;
		int yw1_;
		int xw2_;
		int yw2_;
		int xh_;
		int yh_;
		int xsolution_;
		int ysolution_;

};

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
