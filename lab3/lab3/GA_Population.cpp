#include "GA_Population.hpp"

using namespace std;

GA_Population::GA_Population(const GA_Population & other) : Population(other)
{
	this->d_totalFitness = other.d_totalFitness;
	this->probabilities = other.probabilities;
} // end Copy Constructor


inline double GA_Population::totalFitness(void) const
{
	return d_totalFitness;
} // end method totalFitness


void GA_Population::evaluateAll(fitnessFunction f)
{
	d_totalFitness = 0;

	for (auto& g : genes)
	{
		g.evaluate(f);
		d_totalFitness += g.fitness();
	} // end for
} // end method evaluateAll


void GA_Population::findProbabilities(fitnessFunction f)
{
	evaluateAll(f);
	sort();

	double  d_worst = genes[size() - 1].fitness(),
			d_offset = 0.0;

	for (size_t i = 0; i < size(); i++)
	{
		// we are mapping the set of fitness values into the positive real numbers by subtracting all values
		// from the highest fitness values. This will result in the range [0,worst_fitness-min_fitness]
		// the offset is the running total of probabilities
		probabilities.push_back(d_offset + ((d_worst - genes[i].fitness()) / totalFitness()));
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