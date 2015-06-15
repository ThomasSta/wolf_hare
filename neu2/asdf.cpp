
#include <vector>
#include <stack>
#include <utility>

typedef std::vector <std::pair <int, int> > stack; 



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

	return 0;
}
