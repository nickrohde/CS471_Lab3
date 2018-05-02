#include "GA.hpp"

using namespace std;

results_t* geneticAlgorithm(fitnessFunction f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const Mutation_Info& MUT_INFO)
{
	throw not_implemented();
}


Offspring* crossingOver(const Gene& PARENT_A, const Gene& PARENT_B, const Crossing_Over_Info& CO_INFO)
{
	Offspring* res = new Offspring();

	// getRandomNumberInRage returns a number in range [a,b), thus we need to add a little bit to b to make it range [0,1]
	if (getRandomNumberInRange<double>(0.0, (1.0 + std::numeric_limits<double>::min())) < CO_INFO.d_CROSSING_OVER_RATE)
	{
		for (size_t i = 0; i < CO_INFO.ui_NUM_OFFSPRING; i++)
		{
			res->offsprings.push_back(Gene(PARENT_A, PARENT_B, ))
		} // end for

	} // end if
	else
	{
		res->offsprings.push_back(PARENT_A);
		res->offsprings.push_back(PARENT_B);

		// if the population is supposed to grow, we will randomly replicate the parents until we have enough offspring
		if (ui_NUM_OFFSPRING > 2)
		{
			for (size_t i = 2; i <= ui_NUM_OFFSPRING; i++)
			{
				if (getRandomNumberInRange<size_t>(0, 2) % 2) // range is [0,2) = [0,1]
				{
					res->offsprings.push_back(PARENT_A);
				} // end if
				else
				{
					res->offsprings.push_back(PARENT_B);
				} // end else
			} // end for
		} // end if
	} // end else

	return res;
} // end method crossingOver
