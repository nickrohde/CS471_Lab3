#include "SelectionStrategy.hpp"

using namespace std;

Parents* SelectionStrategy::selectParents(const Population& pop, StrategyType t)
{
	Parents* p = new Parents();
	function<Gene*(const Population&)> f;

	switch (t)
	{
	case SelectionStrategy::StrategyType::Roulette:
		f = roulette;
		break;
	case SelectionStrategy::StrategyType::Proportionate:
		f = proportionate;
		break;
	case SelectionStrategy::StrategyType::Rank:
		f = rank;
		break;	
	case SelectionStrategy::StrategyType::SteadyState:
		f = steadyState;
		break;
	case SelectionStrategy::StrategyType::Tournament:
		f = tournament;
		break;
	default:
		throw invalid_argument("Invalid type received by selectParents.");
	} // end switch

	p->parent_A = f(pop);
	p->parent_B = f(pop);

	// ensure parents are unique
	while (p->parent_A == p->parent_B)
	{
		p->parent_A = f(pop);
	} // end while

	return p;
} // end method selectParents


Gene* SelectionStrategy::tournament(const Population & pop)
{
	throw not_implemented();
} // end method tournament


Gene* SelectionStrategy::roulette(const Population & pop)
{
	vector<double>* probabilities = findProbabilities(pop);

	// our random number is in the range [0, total_probabilities]
	double	d_rand = getRandomNumberInRange<double>(0.0, vectorSum(probabilities));

	Gene* selected = &(pop[0]);

	for (size_t i = 0; i < probabilities->size(); i++)
	{
		// if probability[i] <= rand < probability[i+1], the individual i was selected
		if (probabilities->at(i) > d_rand)
		{
			break;
		} // end if

		selected = &(pop[i]);
	} // end for

	delete probabilities;

	return selected;
} // end method roulette


Gene* SelectionStrategy::proportionate(const Population & pop)
{
	throw not_implemented();
} // end method proportionate


Gene* SelectionStrategy::rank(const Population & pop)
{
	throw not_implemented();
} // end method rank


Gene* SelectionStrategy::steadyState(const Population & pop)
{
	throw not_implemented();
} // end method steadyState


vector<double>* SelectionStrategy::findProbabilities(const Population & pop)
{
	double  d_worst = pop[pop.size() - 1].fitness(),
			d_offset = 0.0;

	vector<double>* probabilities = new vector<double>();

	for (size_t i = 0; i < pop.size(); i++)
	{
		// we are mapping the set of fitness values into the positive real numbers by subtracting all values
		// from the highest fitness values. This will result in the range [0,worst_fitness-min_fitness]
		// the offset is the running total of probabilities
		probabilities->push_back(d_offset + ((d_worst - pop[i].fitness()) / pop.totalFitness()));
		d_offset = probabilities->at(i);
	} // end for
	
	return probabilities;
} // end method findProbabilities
