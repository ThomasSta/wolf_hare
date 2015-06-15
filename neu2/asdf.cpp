
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
		//std::cout << paths.size() << std::endl;
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

	int sizeX	= 5;
	int sizeY	= 5;

	int goalX	= sizeX - 1;
	int goalY	= sizeY - 1;

	int w1_startX	= 0;
	int w1_startY	= 1;

	int w2_startX	= 0;
	int w2_startY	= 3;
	
	int h_startX	= 2;
	int h_startY	= 0;
	
	stack curStack;
	std::vector<stack> paths_w1;	
	std::vector<stack> paths_w2;	
	std::vector<stack> paths_h;	


	assemblePaths
	(goalX
	,goalY
	,w1_startX
	,w1_startY
	,curStack
	,paths_w1
	);

	assemblePaths
	(goalX
	,goalY
	,w2_startX
	,w2_startY
	,curStack
	,paths_w2
	);

	assemblePaths
	(goalX
	,goalY
	,h_startX
	,h_startY
	,curStack
	,paths_h
	);

	std::vector<std::vector<std::vector <int> > > route_lengths;//(paths_w1.size());
	route_lengths.resize(paths_w1.size());
	for (int i = 0; i < route_lengths.size(); ++i)
	{
		route_lengths[i].resize(paths_w2.size());	
		for (int j = 0; j < route_lengths[0].size(); ++j)
		{
		
			route_lengths[i][j].resize(paths_h.size());
		}
	}
	std::cout << paths_w1.size() << std::endl;
	std::cout << paths_w2.size() << std::endl;
	std::cout << paths_h.size() << std::endl;

	for(int i = 0; i < paths_w1.size(); ++i)
	{
		for(int j = 0; j < paths_w2.size(); ++j)
		{
	
			calcTask
			(paths_w1[i]
			,paths_w2[j]
			,paths_h
			,route_lengths[i][j]	// list with number of steps to get the hare or -1 if hare faster
			);		
			
			
			for(int k = 0; k < route_lengths[i][j].size(); ++k)
			{
				std::cout << route_lengths[i][j][k] << std::endl;		
			}
		}
	}

#if 0
	for (int i = 0; i < paths.size(); i++)
	{
		//printPath(paths[i], sizeX, sizeY);
		//std::cout << std::endl;
	}
#endif
	return 0;
}
