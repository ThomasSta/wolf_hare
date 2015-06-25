#include <vector>
#include <stack>
#include <utility>
#include <iostream>
#include <climits>
#include <mpi.h>
#include <malloc.h>

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
	(int 					sizeX
	,int					sizeY
	,int 					goalX
	,int 					goalY
	,int					startX
	,int 					startY
	,stack					curStack
	,std::vector< stack > &	paths
	,bool					allPaths	// if true, not only the paths that directly lead to the target are used
	,int					maxSteps	// maximum number of steps
	,int 					curSteps = -1
	)
{
	

	curStack.push_back(std::pair<int, int>(startX, startY));
	curSteps++;
	
	if (	(!allPaths && startX == goalX && startY == goalY)
		||	(curSteps == maxSteps))
	{
		paths.push_back(stackCpy(curStack));
		curStack.pop_back();
		curSteps--;
		return;
	}	

	else
	{
		// up
		if (	(allPaths || goalY > startY) 
			&& 	!containsPair(curStack, startX, startY + 1)
			&& curSteps < maxSteps
			&& startX >= 0
			&& startX < sizeX
			&& startY + 1 >= 0
			&& startY + 1 < sizeY)
		{
			assemblePaths
				(sizeX
				,sizeY
				,goalX
				,goalY
				,startX
				,startY + 1
				,curStack
				,paths
				,allPaths
				,maxSteps
				,curSteps
				);
		}
	
		// down
		if (	(allPaths || goalY < startY) 
			&& 	!containsPair(curStack, startX, startY - 1)
			&& curSteps < maxSteps
			&& startX >= 0
			&& startX < sizeX
			&& startY - 1 >= 0
			&& startY - 1 < sizeY)
		{
			assemblePaths
				(sizeX
				,sizeY
				,goalX
				,goalY
				,startX
				,startY - 1
				,curStack
				,paths
				,allPaths
				,maxSteps
				,curSteps
				);
		}

		// left
		if (	(allPaths || goalX < startX) 
			&& 	!containsPair(curStack, startX - 1, startY)
			&& curSteps < maxSteps
			&& startX - 1 >= 0
			&& startX - 1 < sizeX
			&& startY >= 0
			&& startY < sizeY)
		{
			assemblePaths
				(sizeX
				,sizeY
				,goalX
				,goalY
				,startX - 1 
				,startY
				,curStack
				,paths
				,allPaths
				,maxSteps
				,curSteps
				);
		}
		
		// right
		if (	(allPaths || goalX > startX) 
			&& 	!containsPair(curStack, startX + 1, startY)
			&& curSteps < maxSteps
			&& startX + 1 >= 0
			&& startX + 1 < sizeX
			&& startY >= 0
			&& startY < sizeY)
		{
			assemblePaths
				(sizeX
				,sizeY
				,goalX
				,goalY
				,startX + 1
				,startY
				,curStack
				,paths
				,allPaths
				,maxSteps
				,curSteps
				);
		}
#if 0
		// no move
		assemblePaths
			(sizeX
			,sizeY
			,goalX
			,goalY
			,startX
			,startY
			,curStack
			,paths
			,allPaths
			,maxSteps
			,curSteps
			);
#endif

		curStack.pop_back();
		curSteps--;

	}
}

void
calcTask
	(stack & w1
	,stack & w2
	,std::vector<stack> & h
	,int *route_length	// list with number of steps to get the hare or -1 if hare faster
	,int w1_index
	,int w2_index
	,int w2_length
	,int h_length
	)
{

//	route_length.resize(h.size());
	int tmp[h.size()];


	// loop over hare routes
	// OpenMP
	for (int i = 0; i < h.size(); i++)
	{
		int counter = 0;
		int h_idx	= 0;
		int w1_idx 	= 0;
		int w2_idx 	= 0;

		stack & h_stack = h[i];
		// stack::iterator h_it 	= h[i].begin();	
		// stack::iterator w1_it 	= w1.begin();
		// stack::iterator w2_it 	= w2.begin();	

		while (true)
		{

			// std::cout << h_it->first << " " << h_it->second << std::endl;

			// wolf 1 on hare
			if (	w1[w1_idx].first 	== h_stack[h_idx].first
				&& 	w1[w1_idx].second	== h_stack[h_idx].second)
			{
				tmp[i] = counter;
				break;
			}

			// wolf 2 on hare
			if (	w2[w2_idx].first 	== h_stack[h_idx].first
				&& 	w2[w2_idx].second	== h_stack[h_idx].second)
			{
				tmp[i] = counter;
				break;
			}

			// hare at goal
			if (h_idx == h_stack.size()-1)
			{
				tmp[i] = -1;
				break;
			}
			
			if (w1_idx < w1.size()-1) w1_idx++;
			if (w2_idx < w2.size()-1) w2_idx++;
			
			h_idx++;
			counter++;
		}
	}

	for (int i = 0; i < h.size(); i++)
	{
		route_length[w1_index*w2_length*h_length + w2_index*h_length + i] = tmp[i];
	}

}


std::vector< std::pair <int, int> >
reduceRoutes
	(int *routes, int w1Size, int w2Size, int hSize
	)
{
	std::vector < std::pair <int, int> >  best_wolf_pairs;

	int wolves_win_counter 	= 0;
	int wolves_win_sum		= INT_MAX;

	for (int i = 0; i < w1Size; i++)
	{
		for (int j = 0; j < w2Size; j++)
		{
			int wolves_win_counter_local 	= 0;
			int wolves_win_sum_local 		= 0;
			for (int k = 0; k < hSize; k++)
			{
				std::cout << "i: " << i << " j: " << j << " k: " << k << " index: " << i*w2Size*hSize + j*hSize + k << " inhalt: " << routes[i*w2Size*hSize + j*hSize + k] << std::endl; 
				if (routes[i*w2Size*hSize + j*hSize + k] != -1) 
				{
					wolves_win_counter_local++;		
					wolves_win_sum_local += routes[i*w2Size*hSize + j*hSize + k];
				}
			}

			if (wolves_win_counter_local 	> wolves_win_counter)
			{
				wolves_win_counter 	= wolves_win_counter_local;
				wolves_win_sum		= wolves_win_sum_local;
				best_wolf_pairs.resize(1);
				best_wolf_pairs[0] = std::pair<int, int>(i, j);
			} 	
			
			else if (wolves_win_counter_local == wolves_win_counter && wolves_win_sum_local < wolves_win_sum)
			{
				wolves_win_sum = wolves_win_sum_local;
				best_wolf_pairs.resize(1);
				best_wolf_pairs[0] = std::pair<int, int>(i, j);
			}

			else if (	wolves_win_counter_local == wolves_win_counter
				&& 	wolves_win_sum_local 	 ==  wolves_win_sum)
			{
				best_wolf_pairs.push_back(std::pair<int, int>(i, j));
			} 	
		}
	
	}

	std::cerr << "Best route, number of wins (wolf catches hare): " << wolves_win_counter << std::endl;	
	std::cerr << "Best route, steps needed when caught (average): " << (float)wolves_win_sum / (float)wolves_win_counter << std::endl;	

	return best_wolf_pairs;
		
	
}

void print(int *route_lengthsRecv, int w1, int w2, int h)
{
	for( int i = 0; i < w1; i++)
	{
		for( int j = 0; j < w2; j++)
		{
			for( int k = 0; k < h; k++)
			{
				std::cout << "\ti: " << i << " j: " << j << " k: " << k << std::endl; 
				std::cout << "Laenge: " << route_lengthsRecv[i*w2*h + j*h + k] << std::endl; 
			} 
		} 
	}
}		


int main(int argc, char **args)
{

	MPI_Init(&argc, &args);

	int size;
	int rank;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Request reqs[size];
	MPI_Status stats[size];

	int sizeX	= 4;
	int sizeY	= 4;

	int goalX	= sizeX - 1;
	int goalY	= sizeY - 1;

	int w1_startX	= 0;
	int w1_startY	= 0;

	int w2_startX	= 0;
	int w2_startY	= 4;
	
	int h_startX	= 0;
	int h_startY	= 2;
	
	stack curStack;
	std::vector<stack> paths_w1;	
	std::vector<stack> paths_w2;	
	std::vector<stack> paths_h;	

	std::cerr << "Assembling paths..." << std::endl;

	assemblePaths
	(sizeX
	,sizeY
	,goalX
	,goalY
	,w1_startX
	,w1_startY
	,curStack
	,paths_w1
	,true
	,sizeX + sizeY
	);

	assemblePaths
	(sizeX
	,sizeY
	,goalX
	,goalY
	,w2_startX
	,w2_startY
	,curStack
	,paths_w2
	,true
	,sizeX + sizeY
	);

	assemblePaths
	(sizeX
	,sizeY
	,goalX
	,goalY
	,h_startX
	,h_startY
	,curStack
	,paths_h
	,false
	,sizeX + sizeY
	);

	std::cerr << "\nNumber of routes:" << std::endl;
	std::cerr << "Wolf 1:\t" << paths_w1.size() << std::endl;
	std::cerr << "Wolf 2:\t" << paths_w2.size()	<< std::endl;
	std::cerr << "Hare:\t" << paths_h.size() << std::endl;
	std::cerr << "\nNumber of tasks (w1 * w2): " << paths_w1.size() * paths_w2.size() << std::endl;

	int start;
	int end;

	if(rank == size - 1)
	{
		start = rank*(paths_w1.size()/size);
		end = paths_w1.size();
	}else{
		start = rank * (paths_w1.size() / size);
		end = (rank + 1) * (paths_w1.size() / size);
	}
	
	std::cout << "rank: " << rank << " start: " << start << " end: " << end << std::endl;
	
	std::cerr << "\nAllocating space for route comparison..." << std::endl;
	int route_lengths[(end-start)*paths_w2.size()*paths_h.size()];

	std::cerr << "\nComparing paths..." << std::endl;

	for(int i = start; i < end; ++i)
	{
		for(int j = 0; j < paths_w2.size(); ++j)
		{
			
			// std::cerr << "Starting task: w1 = " << i << "/" << paths_w1.size() << "\tw2 = " << j << "/" << paths_w2.size() << std::endl; 

			calcTask
			(paths_w1[i]
			,paths_w2[j]
			,paths_h
			,route_lengths		// list with number of steps to get the hare or -1 if hare faster
			,i-start
			,j
			,paths_w2.size()
			,paths_h.size()
			);		
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);

	if(rank == 0)
	{
		int route_lengthsRecv[paths_w1.size()*paths_w2.size()*paths_h.size()];
	
		//Copy values calculated by rank 0 into big array	
		for( int i = 0; i < end-start; i++)
		{
			for( int j = 0; j < paths_w2.size(); j++)
			{
				for( int k = 0; k < paths_h.size() ; k++)
				{
					route_lengthsRecv[i*paths_w2.size()*paths_h.size() + j*paths_h.size() + k] = route_lengths[i*paths_w2.size()*paths_h.size() + j*paths_h.size() + k];
				} 		
			} 
		} 

		//receiving calculated values from all other ranks
		for( int i = 1; i < size; i++)
		{
			MPI_Recv(&route_lengthsRecv[i*((paths_w1.size()*paths_w2.size()*paths_h.size())/size)], (end-start)*paths_w2.size()*paths_h.size(), MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE); // &reqs[i]);
		}			
			
//last rank may have more paths to calculate
//			MPI_Recv(&route_lengthsRecv[i*((paths_w1.size()*paths_w2.size()*paths_h.size())/size)], (end-start)*paths_w2.size()*paths_h.size(), MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE); //, &status[i]);

//		print(route_lengthRecv, paths_w1.size(), paths_w2.size(), paths_h.size());

		std::cerr << "Reducing routes..." << std::endl;
		std::vector< std::pair<int,int> > best_wolves = reduceRoutes(route_lengthsRecv, paths_w1.size(), paths_w2.size(), paths_h.size());
		std::cerr << "Num best routes: " << best_wolves.size() << std::endl;
	
		for (int i = 0; i < best_wolves.size(); i++)
		{
			std::cout << "w1 = " << best_wolves[i].first << "\tw2 = " << best_wolves[i].second << std::endl;
		}	
	
	#if 0
		for (int i = 0; i < paths_w1.size(); i++)
		{
			for (int j = 0; j < paths_w2.size(); j++)
			{
				std::cout << "WOLF PATHS: w1 = " << i << ", w2 = " << j << std::endl;
				std::cout << "WOLF 1:" << std::endl;
				printPath(paths_w1[i], sizeX, sizeY);
				std::cout << std::endl;
				std::cout << "WOLF 2:" << std::endl;
				printPath(paths_w2[j], sizeX, sizeY);
				std::cout << std::endl;
				for (int k = 0; k < paths_h.size(); k++)
				{
					std::cout << "Length = " << route_lengthsRecv[i*paths_w1.size()*paths_h.size() + j*paths_h.size() + k] << std::endl;
					std::cout << std::endl;
				}
				for (int k = 0; k < paths_h.size(); k++)
				{
					printPath(paths_h[k], sizeX, sizeY);
					std::cout << std::endl;
				}
				std::cout << std::endl;
			
			}
		}
	
	#endif

	}else{
		MPI_Send(&route_lengths[0], (end-start)*paths_w2.size()*paths_h.size(), MPI_INT, 0, 0, MPI_COMM_WORLD); //, &reqs[rank]); //+(size-1)]);
	}
	
	MPI_Barrier(MPI_COMM_WORLD);

	std::cout << "rank: " << rank << std::endl;
	MPI_Finalize();

	return 0;
}
