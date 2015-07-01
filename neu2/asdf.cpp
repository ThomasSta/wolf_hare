#include <vector>
#include <stack>
#include <utility>
#include <iostream>
#include <climits>
#include <mpi.h>
#include <malloc.h>
#include <sys/time.h>
//#include "Timer.hh"

typedef std::vector <std::pair <int, int> > stack; 

//size board
#define SIZEX 5 
#define SIZEY 5

//start wolf1
#define	XW1 3
#define YW1 1
#define W1_ALL_PATHS (true)

//start wolf2
#define XW2 4
#define YW2 0
#define W2_ALL_PATHS (true)
	
//start hare
#define XH 1
#define YH 3
#define H_ALL_PATHS (false)

int p_global = 0;
int length_global = 1000000;
std::vector< std::pair <int, int> > best_wolves;

void print(int *successes, int size)
{
	for( int i = 0; i < size; i+=2)
	{
		std::cout << " w1: " << successes[i] << " w2: " << successes[i+1] << std::endl; 
	}
}		


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
	,int	width
	,int	startX
	,int	startY)
{
	//for (int k = 0; k < path.size(); ++k )
	//{   
	//	std::cout << "x: " << path[k].first << " y: " << path[k].second << std::endl;
	//}

    // Print the path inverted.
    // (0,0) is the bottom left corner.
    for (int j = height - 1; j >= 0; --j)
    {   
        for (int i = 0; i < width; ++i)
        {   
            bool printed = false;
			if(i == startX && j == startY)
			{
				std::cout << "X";
            	std::cout << ' ';
				printed = true;
				continue;
			}else if(i == SIZEX-1 && j == SIZEY-1)
			{
				std::cout << "O";
            	std::cout << ' ';
				printed = true;
				continue;
   			}
            for (int k = 0; k < path.size(); ++k )
            {
				if (containsPair(path, i, j ) && printed == false)
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
	,int w1_index
	,int w2_index
	)
{

//	route_length.resize(h.size());
	short tmp[h.size()];

	int p_local = 0;
	int length_local = 0;
		
	int winW1	= 0;
	int winW2	= 0;

	// loop over hare routes
	// OpenMP
	for (int i = 0; i < h.size(); i++)
	{
		short counter = 0;
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
				
				p_local += 1;
				length_local += counter;
				winW1 = 1;
				break;
			}

			// wolf 2 on hare
			if (	w2[w2_idx].first 	== h_stack[h_idx].first
				&& 	w2[w2_idx].second	== h_stack[h_idx].second)
			{
				p_local += 1;
				length_local += counter;
				winW2 = 1;
				break;
			}

			// hare at goal
			if (h_idx == h_stack.size()-1)
			{
				break;
			}
			
			if (w1_idx < w1.size()-1) w1_idx++;
			if (w2_idx < w2.size()-1) w2_idx++;
			
			h_idx++;
			counter++;
		}
	}
//std::cout << "p_local: " << p_local << " length_local: " << length_local << " p_global: " << p_global << " length_global: " << length_global << std::endl; 
//EIN ELEMENT IM VECTOR BESTEHT AUS W1 UND W2 INDEX PAARE. LÄNGE UND WAHRSCHEINLICHKEIT IN P_GLOBAL UND LENGTHS_GLOBAL GESPEICHERT!!
		if(p_local > p_global)
		{
			p_global = p_local;
			length_global = length_local;
			/*lösche alles aus vector und füge das neue beste element ein */
			best_wolves.resize(1);
			best_wolves[0] = std::pair <int, int> (w1_index, w2_index);
		}else if(p_local == p_global && length_local < length_global)
		{
			length_global = length_local;
			/*lösche alles aus vector und füge das neue beste element ein */
			best_wolves.resize(1);
			best_wolves[0] = std::pair <int, int> (w1_index, w2_index);
		}else if(p_local == p_global && length_local == length_local && p_local != 0)
		{
			/*hänge element an vector an */
			if(winW1 == 1 && winW2 == 0)
			{
				for( int i = 0; i < best_wolves.size(); i++)
				{
					if(best_wolves[i].first == w1_index && best_wolves[i].second == 0)
					{
						best_wolves[i].second = -1; 
						return;
					}
					if(best_wolves[i].first == w1_index && best_wolves[i].second == -1) return;
				}
				best_wolves.push_back(std::pair <int, int> (w1_index, -1));
				return;
			}
			if(winW1 == 0 && winW2 == 1)
			{
				for( int i = 0; i < best_wolves.size(); i++)
				{
					if(best_wolves[i].first == 0 && best_wolves[i].second == w2_index)
					{
						best_wolves[i].first = -1;
						return;
					}
					if(best_wolves[i].first == -1 && best_wolves[i].second == w2_index) return;
				}
				best_wolves.push_back(std::pair <int, int> (-1, w2_index));
				return;
			}
			best_wolves.push_back(std::pair <int, int> (w1_index, w2_index));
		}

}


std::vector< std::pair <int, int> >
reduceRoutes
	(short *routes, int size
	)
{
	std::vector < std::pair <int, int> >  best_wolf_pairs;

	int wolves_win_counter 	= 0;
	int wolves_win_sum		= INT_MAX;

	int wolves_win_counter_local 	= 0;
	int wolves_win_sum_local 		= 0;

	for (int i = 0; i < size; i+=3)
	{

		if(i == 0)
		{
			wolves_win_counter_local = 1;
			wolves_win_sum_local += routes[2];
			i+=3;
		}
		if(routes[i] == routes[i-3] && routes[i+1] == routes[i-2]) 
		{
			wolves_win_counter_local++;		
			wolves_win_sum_local += routes[i+2];
			continue;
		}
		if (wolves_win_counter_local 	> wolves_win_counter)
		{
			wolves_win_counter 	= wolves_win_counter_local;
			wolves_win_sum		= wolves_win_sum_local;
			best_wolf_pairs.resize(1);
			best_wolf_pairs[0] = std::pair<int, int>(routes[i-3], routes[i-2]);
		} 	
		
		else if (wolves_win_counter_local == wolves_win_counter && wolves_win_sum_local < wolves_win_sum)
		{
			wolves_win_sum = wolves_win_sum_local;
			best_wolf_pairs.resize(1);
			best_wolf_pairs[0] = std::pair<int, int>(routes[i-3], routes[i-2]);
		}

		else if (	wolves_win_counter_local == wolves_win_counter
			&& 	wolves_win_sum_local 	 ==  wolves_win_sum)
		{
			best_wolf_pairs.push_back(std::pair<int, int>(routes[i], routes[i+1]));
		}
		
		wolves_win_counter_local 	= 0;
		wolves_win_sum_local 		= 0;
	
	}

	std::cout << "Best route, number of wins (wolf catches hare): " << wolves_win_counter << std::endl;	
	std::cout << "Best route, steps needed when caught (average): " << (float)wolves_win_sum / (float)wolves_win_counter << std::endl;	

	return best_wolf_pairs;
		
	
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

	int sizeX	= SIZEX;
	int sizeY	= SIZEY;

	int goalX	= SIZEX - 1;
	int goalY	= SIZEY - 1;

	int w1_startX	= XW1;
	int w1_startY	= YW1;

	int w2_startX	= XW2;
	int w2_startY	= YW2;
	
	int h_startX	= XH;
	int h_startY	= YH;
	
	stack curStack;
	std::vector<stack> paths_w1;	
	std::vector<stack> paths_w2;	
	std::vector<stack> paths_h;	

	if(rank == 0)
	{
		std::cout << "Assembling paths..." << std::endl;
	}

	assemblePaths
	(sizeX
	,sizeY
	,goalX
	,goalY
	,w1_startX
	,w1_startY
	,curStack
	,paths_w1
	,W1_ALL_PATHS
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
	,W2_ALL_PATHS
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
	,H_ALL_PATHS
	,sizeX + sizeY
	);

	if(rank == 0){
		std::cout << "\nNumber of routes:" << std::endl;
		std::cout << "Wolf 1:\t" << paths_w1.size() << std::endl;
		std::cout << "Wolf 2:\t" << paths_w2.size()	<< std::endl;
		std::cout << "Hare:\t" << paths_h.size() << std::endl;
		std::cout << "\nNumber of tasks (w1 * w2): " << paths_w1.size() * paths_w2.size() << std::endl;
	}
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
	
	MPI_Barrier(MPI_COMM_WORLD);
	std::cout << "rank: " << rank << " start: " << start << " end: " << end << std::endl;
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank == 0)
	{
		std::cout << "\nComparing paths..." << std::endl;
	}

	struct timeval t0, t;
	if(rank == 0)
	{
		gettimeofday(&t0, NULL);
	}

	for(int i = start; i < end; ++i)
	{
		for(int j = 0; j < paths_w2.size(); ++j)
		{
			
			calcTask
			(paths_w1[i]
			,paths_w2[j]
			,paths_h
			,i
			,j
			);		
		}
	}
	
	MPI_Barrier(MPI_COMM_WORLD);

	if(rank == 0)
	{
		gettimeofday(&t, NULL);
		std::cout << "Time for calculating best way: " << ((int) (t.tv_sec - t0.tv_sec) * (int)1000000 + (int)t.tv_usec - (int)t0.tv_usec) * 1e-3 << " ms" << std::endl;;
	}
	
	//copy the vector to an Array (easier to send)
	int bestWolvesArray[best_wolves.size()*2];
	for(int i = 0; i < best_wolves.size(); i++)
	{
		bestWolvesArray[2*i] = best_wolves[i].first;
		bestWolvesArray[2*i+1] = best_wolves[i].second;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	//how many successes has each rank
	int p_rank[size];	
	MPI_Allgather(&p_global, 1, MPI_INT, &p_rank, 1, MPI_INT, MPI_COMM_WORLD);
	//whats the shortest way for_each rank
	int length_rank[size];	
	MPI_Allgather(&length_global, 1, MPI_INT, &length_rank, 1, MPI_INT, MPI_COMM_WORLD);

	int bestRanks[size];
	int bestP = 0;
	int bestL = 1000000;
	
	if(rank == 0){
	//decide who hast the best wolves by looking at p and length of each rank
		for( int i = 0; i < size; i++)
		{
			if(p_rank[i] > bestP)
			{
				for( int j = 0; j < size; j++)
				{
					bestRanks[j] = 0;
				}
				bestRanks[i] = 1;
				bestP = p_rank[i];
				bestL = length_rank[i];
			}else if(p_rank[i] == bestP && length_rank[i] < bestL)
			{
				for( int j = 0; j < size; j++)
				{
					bestRanks[j] = 0;
				}
				bestRanks[i] = 1;
				bestP = p_rank[i];
				bestL = length_rank[i];
			}else if(p_rank[i] == bestP && length_rank[i] == bestL)
			{
				bestRanks[i] = 1;
			}
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&bestRanks, size, MPI_INT, 0, MPI_COMM_WORLD);

//how many best wolves has every rank
	int numOfEl[size];
	int x = 0;
	int numWolves = best_wolves.size()*2;
	for( int i = 0; i < size; i++)
	{
		numOfEl[i] = 0;
	}
	numOfEl[rank] = numWolves;

//if root decided that you have one of the best wolves send them to root, numWolves ^= number of best wolves the prozess rank has
	if(rank != 0)
	{
		if(bestRanks[rank] == 1){
			MPI_Send(&numWolves, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}else{
			MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}else if(rank == 0)
	{
		(bestRanks[0] == 1)  ? numOfEl[0] = numWolves : numOfEl[0] = 0;
		for( int i = 1; i < size; i++)
		{
			MPI_Recv(&numOfEl[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		}
	}
	


	if(rank == 0)
	{

		int allBestCount = 0;

		for( int i = 0; i < size; i++)
		{
			allBestCount += numOfEl[i];
		}
	
		int allBest[allBestCount];
		for( int i = 0; i < best_wolves.size(); i++)
		{
			allBest[2*i] = best_wolves[i].first;
			allBest[2*i+1] = best_wolves[i].second;
		}

		int startIndexRanks[size];
		for( int i = 0; i < size; i++)
		{
			startIndexRanks[i] = 0;
		}
		for( int i = 0; i < size; i++)
		{
			for( int j = 0; j < i; j++)
			{
				startIndexRanks[i] += numOfEl[j];
			}
		}
		
		//receiving calculated values from all other ranks
		for( int i = 1; i < size; i++)
		{
			if(numOfEl[i] == 0) continue;
			MPI_Recv(&allBest[startIndexRanks[i]], numOfEl[i], MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE); // &reqs[i]);
		}

		std::cout << std::endl;
		std::cout << "all best pairs of routes:" << std::endl;
		std::cout << std::endl;

		print(allBest, allBestCount); 
		
		int countAll = 0;
		for(int i = 0; i < allBestCount; i+=2)
		{
    		if(allBest[i] == -1) countAll += paths_w1.size();
			else if(allBest[i+1] == -1) countAll += paths_w2.size();
			else countAll++;
		}
 
		std::cout << std::endl; 

		std::cout << std::endl; 
		std::cout << "best propability: " << (double)bestP/paths_h.size() << std::endl; 
		std::cout << "average catch probability: " << (double)(((double)countAll)/(paths_w1.size()*paths_w2.size())) << std::endl; 
		std::cout << "shortest way: " << (double)bestL/paths_h.size() << std::endl;
		std::cout << std::endl; 
#if 1
		std::cout << "Routes hare: " << std::endl;
		for (int k = 0; k < paths_h.size(); k++)
		{
			std::cout << std::endl; 
			printPath(paths_h[k], sizeX, sizeY, XH, YH);
			std::cout << std::endl;
		}
		std::cout << std::endl; 
		std::cout << "paths_w1 size: " << paths_w1.size() << std::endl;
		std::cout << "paths_w2 size: " << paths_w2.size() << std::endl;
		std::cout << std::endl; 

		std::cout << "Best wolf routes: " << std::endl; 
		for (int i = 0; i < allBestCount; i+=2)
		{
			//std::cout << "w1 = " << best_wolves[i].first << "\tw2 = " << best_wolves[i].second << std::endl;
		
			if(allBest[i] != -1)
			{
				std::cout << std::endl; 
				std::cout << "w1 with route " << allBest[i] << " catches the hare!" << std::endl;
				std::cout << std::endl;
				printPath(paths_w1[allBest[i]], sizeX, sizeY, XW1, YW1);
				std::cout << std::endl;
			}
			else
			{
				std::cout << std::endl;
				std::cout << "w1 route doesn't matter, w2 with route " << allBest[i+1] << " always catches the hare!" << std::endl;
				std::cout << std::endl;
			}
			if(allBest[i+1] != -1)
			{
				std::cout << "w2 with route " << allBest[i+1] << " catches the hare! " << std::endl;
				std::cout << std::endl; 
				printPath(paths_w2[allBest[i+1]], sizeX, sizeY, XW2, YW2);
				std::cout << std::endl; 
			}
			else
			{
				std::cout << std::endl;
				std::cout << "w2 route doesn't matter, w1 with route " << allBest[i] << " always catches the hare!" << std::endl;
				std::cout << std::endl;
			}
				std::cout << std::endl;
				std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		}	
#endif 	
	}else{
		if(bestRanks[rank] == 1) MPI_Send(&bestWolvesArray[0], numWolves, MPI_INT, 0, 0, MPI_COMM_WORLD); //, &reqs[rank]); //+(size-1)]);
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();

	return 0;
}
