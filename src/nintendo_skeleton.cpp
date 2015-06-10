#include <iostream>
#include <cstdlib>

class FifteenPuzzle
{
	public:
		static const int MAX_NEIGHBORS = 4;

		FifteenPuzzle(const std::string& config="abcdefghijklmnoX")
		{
			for (int y = 0; y < 4; ++y) {
				for (int x = 0; x < 4; ++x) {
					tiles[y * 4 + x] = config[y * 4 + x];
					if (tiles[y * 4 + x] == 'X') {
						cX = x;
						cY = y;
					}
				}
			}
		}

		int neighbors(FifteenPuzzle *hood) const
		{
			int num = 0;
			if (cX > 0) {
				FifteenPuzzle& ref = hood[num];
				ref = *this;
				++num;
				std::swap(ref.tiles[cY * 4 + cX],
						ref.tiles[cY * 4 + cX - 1]);
				--ref.cX;
			}
			if (cX < 3) {
				FifteenPuzzle& ref = hood[num];
				ref = *this;
				++num;
				std::swap(ref.tiles[cY * 4 + cX],
						ref.tiles[cY * 4 + cX + 1]);
				++ref.cX;
			}
			if (cY > 0) {
				FifteenPuzzle& ref = hood[num];
				ref = *this;
				++num;
				std::swap(ref.tiles[cY * 4 + cX],
						ref.tiles[cY * 4 + cX - 4]);
				--ref.cY;
			}
			if (cY < 3) {
				FifteenPuzzle& ref = hood[num];
				ref = *this;
				++num;
				std::swap(ref.tiles[cY * 4 + cX],
						ref.tiles[cY * 4 + cX + 4]);
				++ref.cY;
			}
			return num;
		}

		void print() const
		{
			for (int y = 0; y < 4; ++y) {
				for (int x = 0; x < 4; ++x) 
					std::cout << tiles[y * 4 + x];
				std::cout << "\n";
			}
			std::cout << "\n";
		}

		bool isSolution() const
		{
			for (int i = 1; i < 15; ++i)
				if ((tiles[i - 1] + 1) != tiles[i])
					return false;
			return true;
		}
		
		bool operator==(const FifteenPuzzle& other) const
		{
			for (int i = 0; i < 16; ++i)
				if (tiles[i] != other.tiles[i])
					return false;
			return true;
		}


	private:
		char tiles[16];
		int cX;
		int cY;
};

class Tumbler
{
	public:
		static const int MAX_NEIGHBORS = 5;

		Tumbler(const std::string& config="BabcdXefghBijklXmnopBqrstX")
		{
			int f = 0;
			for (int x = 0; x < 5; ++x) 
			{
				if(x % 2 == 0)
				{
					tiles[x * 5] = config[x * 5];
					tiles[x * 5 + 5] = config[x * 5 + 5];
				}
				
				for (int y = 1; y < 5; ++y) 
				{
					tiles[x * 5 + y] = config[x * 5 + y];
				}
			}
		}

		int neighbors(Tumbler *hood) const
		{
			int num = 0;
			Tumbler& ref0 = hood[num];
			ref0 = *this;
			++num;
			
			//HORIZONTAL MOVEMENT
			//move to the right !only once!
			//move to the left !only once!

			//move to the left top layer
			Tumbler& ref1 = hood[num];
			ref1 = *this;
			++num;

			for(int y = 1; y < 3; y++)
			{
				for(int x = 0; x < 4; x++)
				{
					std::swap(ref1.tiles[x * 5 + y],
						  ref1.tiles[(x+1) * 5 + y]);
				}
			}
		
			//move to the left bottom layer
			Tumbler& ref2 = hood[num];
			ref2 = *this;
			++num;

			for(int y = 3; y < 5; y++)
			{
				for(int x = 0; x < 4; x++)
				{
					std::swap(ref2.tiles[x * 5 + y],
						  ref2.tiles[(x+1) * 5 + y]);
				}
			}

			//move to the right top layer
			Tumbler& ref3 = hood[num];
			ref3 = *this;
			++num;

			for(int y = 1; y < 3; y++)
			{
				for(int x = 4; x > 0; x--)
				{
					std::swap(ref3.tiles[x * 5 + y],
						  ref3.tiles[(x-1) * 5 + y]);
				}
			}
			
			//move to the right bottom layer
			Tumbler& ref4 = hood[num];
			ref4 = *this;
			++num;

			for(int y = 3; y < 5; y++)
			{
				for(int x = 4; x > 0; x--)
				{
					std::swap(ref4.tiles[x * 5 + y],
						  ref4.tiles[(x-1) * 5 + y]);
				}
			}

			//VERTICAL MOVEMENT
			
			//can only be moved up
			if(ref0.tiles[0] == 'X')
			{
				for(int x = 0; x < 5; x+=2)
				{
					for(int y = 0; y < 5; y++)
					{
						std::swap(ref0.tiles[x * 5 + y],
							  ref0.tiles[x * 5 + y + 1]);
					}
				}

			//can only be moved down
			}else if(ref0.tiles[5] == 'X')
			{
				for(int x = 0; x < 5; x+=2)
				{
					for(int y = 5; y > 0; y--)
					{
						std::swap(ref0.tiles[x * 5 + y],
							  ref0.tiles[x * 5 + y - 1]);
					}
				}
			}


			return num;
		}

		void print() const
		{
			std::cout << tiles[0] << " " << tiles[10] << " " << tiles[20] << std::endl;
			for (int y = 1; y < 5; ++y) 
			{
				for (int x = 0; x < 5; ++x) 
				{
					std::cout << tiles[x * 5 + y];
				}
				std::cout << "\n";
			}
			std::cout << tiles[5] << " " << tiles[15] << " " << tiles[25] << std::endl;
			std::cout << "\n";

		}

		bool isSolution() const
		{
			char ref[] = {"BabcdXefghBijklXmnopBqrstX"};
			for (int i = 0; i < 26; ++i)
				if (tiles[i] != ref[i])
					return false;
			return true;
		}
		
		void setTo(Tumbler *used, int index) const
		{
			Tumbler& tumb = used[index];
			tumb = *this;
			for (int i = 0; i < 26; ++i)
			{
				tiles[i] == tumb.tiles[i];
			}
		}


		bool operator==(const Tumbler& other) const
		{
			for (int i = 0; i < 26; ++i)
				if (tiles[i] != other.tiles[i])
					return false;
			return true;
		}


	private:
		char tiles[26];

};

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
				/*
					std::cout << index << std::endl;
					for(int i = 0; i < 3; i++)
					{
						std::cout << i << std::endl;
						used[i].print();
					}
				*/
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

int main()
{
	//trivial:
	//FifteenPuzzle v("Xabc"
	//                "efgd"
	//                "ijkh"
	//                "mnol");

	// unsolvable:
	// FifteenPuzzle v("abcd"
	//                 "efgh"
	//                 "ijkl"
	//                 "monX");

	// takes a while:
	//FifteenPuzzle v("abfd"
	//		  "egXh"
	//		  "jkcl"
	//		  "imno");
	//FifteenPuzzle used[10];

	//Tumbler v("XBcdabefghXBijklmnopXBqrst");
	Tumbler v("XBqrcdabghXBefklijopXBmnst");
	//Tumbler v("XBabidefghXBcjklmnopXBqrst");
	Tumbler used[50];

	std::cout << "starting constellation: " << std::endl;
	v.print();
	std::cout << "solving... " << std::endl;

//	DepthSearch<FifteenPuzzle>()(v, 21);
//	DepthSearchRemember<FifteenPuzzle>()(v, 21, used, 0);
//	DepthSearch<Tumbler>()(v, 15);
	DepthSearchRemember<Tumbler>()(v, 21, used, 0);
	std::cout << "puzzle could not be solved :(" << std::endl;

	return 0;
}
