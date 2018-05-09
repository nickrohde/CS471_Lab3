#include "DE_Population.hpp" // class header

using namespace std;


Gene * DE_Population::best(void)
{
	if (!b_isSorted)
	{
		sort();
	} // end if

	return &(genes[0]);
} // end method best

void DE_Population::evaluateAll(fitnessFunction f)
{
	b_isSorted = false;

	for (auto& g : genes)
	{
		g.evaluate(f);
	} // end for
} // end method evaluateAll
