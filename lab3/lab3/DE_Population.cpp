#include "DE_Population.hpp"

using namespace std;

void DE_Population::evaluateAll(fitnessFunction f)
{
	for (Gene& g : genes)
	{
		g.evaluate(f);
	} // end for
} // end method evaluateAll

inline std::vector<Gene>::iterator DE_Population::begin(void)
{
	return genes.begin();
} // end method begin

inline std::vector<Gene>::iterator DE_Population::end(void)
{
	return genes.end();
} // end method end
