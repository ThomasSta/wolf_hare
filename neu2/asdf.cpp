
#include <vector>
#include <stack>
#include <utility>
#include <iostream>

typedef std::vector <std::pair <int, int> > stack; 

bool
containsPair
	(stack	path
	,int 	x
	,int 	y)
{
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i].first == x && path[i].second == y) return true;
	}

	return false;
}

#define EMPTY   ('.')
#define PATH    ('#')
void
printPath
	(stack 	path
	,int	height
	,int	width)
{
	for (int k = 0; k < path.size(); ++k )
	{   
		std::cout << "x: " << path[k].first << " y: " << path[k].second << std::endl;
	}

    // Print the path inverted.
    // (0,0) is the bottom left corner.
    for (int j = height - 1; j >= 0; --j)
    {   
        for (int i = 0; i < width; ++i)
        {   
            bool printed = false;
            for (int k = 0; k < path.size(); ++k )
            {   
                if (containsPair(path, i, j ))
                {   
                    std::cout << PATH;
                    printed = true;
                    break;
                }   
            }   
            if (!printed) std::cout << EMPTY;
            std::cout << ' ';
        }   
        std::cout << '\n';
    }   
    
}

stack
stackCpy
	(stack in)
{
	stack out;
	
	for (int i = 0; i < in.size(); i++)
	{
		out.push_back(in[i]);
	}

	return out;
}

void
assemblePaths
	(int 					goalX
	,int 					goalY
	,int					startX
	,int 					startY
	,stack					curStack
	,std::vector< stack > &	paths
	)
{
	
	// std::cout << "x: " << startX << " y: " << startY << std::endl;

	curStack.push_back(std::pair<int, int>(startX, startY));
	
	if (startX == goalX && startY == goalY)
	{
		// printPath(curStack, 4, 4);
		paths.push_back(stackCpy(curStack));
		std::cout << paths.size() << std::endl;
		curStack.pop_back();
		return;
	}	

	else
	{
		// up
		if (goalY > startY && !containsPair(curStack, startX, startY + 1))
		{
			assemblePaths
				(goalX
				,goalY
				,startX
				,startY + 1
				,curStack
				,paths);
		}
	
		// down
		if (goalY < startY && !containsPair(curStack, startX, startY - 1))
		{
			assemblePaths
				(goalX
				,goalY
				,startX
				,startY - 1
				,curStack
				,paths);
		}

		// left
		if (goalX < startX && !containsPair(curStack, startX - 1, startY))
		{
			assemblePaths
				(goalX
				,goalY
				,startX - 1 
				,startY
				,curStack
				,paths);
		}
		
		// right
		if (goalX > startX && !containsPair(curStack, startX + 1, startY))
		{
			assemblePaths
				(goalX
				,goalY
				,startX + 1
				,startY
				,curStack
				,paths);
		}

		curStack.pop_back();

	}
}

void
calcTask
	(stack w1
	,stack w2
	,std::vector<stack> h
	,std::vector<int> route_length	// list with number of steps to get the hare or -1 if hare faster
	)
{
	stack::iterator w1_it 	= w1.begin();
	stack::iterator w2_it 	= w2.begin();	

	route_length.resize(h.size());
	int tmp[h.size()];

	int counter = 0;

	// loop over hare routes
	// OpenMP
	for (int i = 0; i < h.size(); i++)
	{
		stack::iterator h_it 	= h[i].begin();	

		while (true)
		{
			// wolf 1 on hare
			if (	w1_it->first 	== h_it->first
				&& 	w1_it->second	== h_it->second)
			{
				tmp[i] = counter;
				break;
			}

			// wolf 2 on hare
			if (	w2_it->first 	== h_it->first
				&& 	w2_it->second	== h_it->second)
			{
				tmp[i] = counter;
				break;
			}

			// hare at goal
			if (h_it == h[i].end())
			{
				tmp[i] = -1;
				break;
			}
			
			if (w1_it != w1.end()) w1_it++;
			if (w2_it != w2.end()) w2_it++;
			
			h_it++;
			counter++;
		}
	}

	for (int i = 0; i < h.size(); i++)
	{
		route_length[i] = tmp[i];
	}

}




int main()
{

	int sizeX	= 10;
	int sizeY	= 10;

	int goalX	= 9;
	int goalY	= 9;

	int startX	= 0;
	int startY	= 0;
	
	stack curStack;
	std::vector<stack> paths1;	
	std::vector<stack> paths2;	
	std::vector<stack> paths3;	

	assemblePaths
	(goalX
	,goalY
	,startX
	,startY
	,curStack
	,paths1
	);

	assemblePaths
	(goalX
	,goalY
	,startX
	,startY
	,curStack
	,paths2
	);

	assemblePaths
	(goalX
	,goalY
	,startX
	,startY
	,curStack
	,paths3
	);

	std::cout << paths1.size() << std::endl;
#if 0
	for (int i = 0; i < paths.size(); i++)
	{
		//printPath(paths[i], sizeX, sizeY);
		//std::cout << std::endl;
	}
#endif
	return 0;
}
