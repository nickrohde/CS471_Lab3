#include "GA_Population.hpp"

using namespace std;

GA_Population::GA_Population(const GA_Population & other) : Population(other)
{
	this->d_totalFitness = other.d_totalFitness;
	this->probabilities = other.probabilities;
} // end Copy Constructor


/*
void GA_Population::evaluateAll(fitnessFunction f)
*/


void GA_Population::findProbabilities(fitnessFunction f)
{
	double  d_worst = genes[size() - 1].fitness(),
			d_offset = 0.0;

	// find total fitness of population
	for (auto& g : genes)
	{
		d_totalFitness += (d_worst - g.fitness());
	} // end for

	for (size_t i = 0; i < size(); i++)
	{
		// we are mapping the set of fitness values into the positive real numbers by subtracting all values
		// from the largest (worst) fitness value. This will result in the range [0,1]
		// the offset is the running total of probabilities, as the individual's fitness increases, it's probability 
		// decreases proportional to the best solution
		probabilities.push_back(d_offset + ((d_worst - genes[i].fitness()) / d_totalFitness));
		d_offset = probabilities.at(i);
	} // end for

} // end method findProbabilities


GA_Population & operator<<(GA_Population & pop, const Offspring * newGenes)
{
	for (auto& g : newGenes->offsprings)
	{
		pop << &g;
	} // end for

	return pop;
} // end operator<<(Population&, const Offspring *)


GA_Population & operator<<(GA_Population & pop, const Gene * newGene)
{
	if (pop.genes.size() > 0)
	{
		if (newGene->length() != pop.genes.at(0).length())
		{
			throw invalid_argument("New genes are not of the same size as genes in population.");
		} // end if
	} // end if

	pop.genes.push_back(*newGene);
	pop.ui_size++;

	return pop;
} // end operator<<(Population &, const Gene *)