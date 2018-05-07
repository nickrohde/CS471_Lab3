#include "DE_Population.hpp"

using namespace std;

DE_Population::DE_Population(const DE_Population & other) : Population(other)
{
}

Gene * DE_Population::best(void)
{
	if (!b_isSorted)
	{
		sort();
	}

	return &(genes[0]);
}
