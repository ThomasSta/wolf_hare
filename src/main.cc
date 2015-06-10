#include <iostream>
#include <cstdlib>

#include "Array.hh"
#include "Game.hh"

int main(int argc, char **argv)
{

	Game test(5,5);
	test.init(1,1,2,3,3,3,4,4);
	test.print();
	
	if(!test.isSolution()) std::cout << "no solution :("  << std::endl;

	std::cout << std::endl;

	test.init(1,1,3,3,3,3,4,4);
	test.print();
	if(test.isSolution()) std::cout << "solution :)"  << std::endl;

	return 0;
}
