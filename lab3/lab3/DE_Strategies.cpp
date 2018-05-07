#include "DE_Strategies.hpp"

using namespace std;


results_t* DifferentialEvolution::differentialEvolution(fitnessFunction f, const DE_Info& DE_INFO, const Population_Info& POP_INFO, const Bounds& BOUNDS, const Mutation_Info& MUT_INFO, const Crossing_Over_Info& CR_INFO, DE_Strategy t)
{
	DE_Function genNoiseVector = differentialEvolutionHelper(t);

	DE_Population* current = new DE_Population(POP_INFO.ui_SIZE, POP_INFO.ui_GENE_DIM, BOUNDS);

	for (size_t gen = 0; gen < POP_INFO.ui_GENERATIONS; gen++)
	{
		DE_Population* new_pop = new DE_Population();

		current->evaluateAll(f);

		for (size_t i = 0; i < POP_INFO.ui_SIZE; i++)
		{
			Gene * noise = genNoiseVector(*current, BOUNDS, DE_INFO);

			noise->evaluate(f);

			if (noise->d_fitness < (*current)[i].d_fitness)
			{
				new_pop->genes.push_back(*noise);
			} // end if
			else
			{
				new_pop->genes.push_back((*current)[i]);
			} // end else

			delete noise;
		} // end for

	} // end for

	return nullptr;
} // end method differentialEvolution


DE_Function DifferentialEvolution::differentialEvolutionHelper(DE_Strategy t)
{
	DE_Function g;

	// determine which strategy to use
	switch (t)
	{
	case DE_Strategy::DE_BEST_1_EXP:
		g = best_1_exp;
		break;
	case DE_Strategy::DE_BEST_2_EXP:
		g = best_2_exp;
		break;
	case DE_Strategy::DE_BEST_1_BIN:
		g = best_1_bin;
		break;
	case DE_Strategy::DE_BEST_2_BIN:
		g = best_1_bin;
		break;
	case DE_Strategy::DE_RAND_1_EXP:
		g = rand_1_exp;
		break;
	case DE_Strategy::DE_RAND_2_EXP:
		g = rand_2_exp;
		break;
	case DE_Strategy::DE_RAND_1_BIN:
		g = rand_1_bin;
		break;
	case DE_Strategy::DE_RAND_2_BIN:
		g = rand_2_bin;
		break;
	case DE_Strategy::DE_RTB_1_EXP:
		g = rtb_1_exp;
		break;
	case DE_Strategy::DE_RTB_1_BIN:
		g = rtb_1_bin;
		break;
	default:
		throw invalid_argument("Differential Evolution received invalid type argument.");
	} // end switch

	return g;
} // end differentialEvolutionHelper


Gene * DifferentialEvolution::best_1(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO)
{
	Gene* noise = new Gene();

	noise->gene.clear();
	noise->gene = vector<double>(POP[0].length());

	double F = getRandomRealInRange<double>(0.5, _ONE);

	for (size_t j = 0; j < POP[0].length(); j++)
	{
		size_t	r1 = getRandomIntInRange<size_t>(0, POP.size()),
				r2 = getRandomIntInRange<size_t>(0, POP.size());

		// ensure i, r1, r2 are unique
		while (i == r1 || i == r2 || r1 == r2)
		{
			r1 = getRandomIntInRange<size_t>(0, POP.size());
			r2 = getRandomIntInRange<size_t>(0, POP.size());
		} // end while

		noise->gene[j] = (best(POP, j) + strat1(POP, F, j, r1, r2));
	} // end for

	return noise;
} // end method best_1_exp


Gene * DifferentialEvolution::best_2(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO)
{
	Gene* noise = new Gene();

	noise->gene.clear();
	noise->gene = vector<double>(POP[0].length());

	double F = getRandomRealInRange<double>(0.5, _ONE);

	for (size_t j = 0; j < POP[0].length(); j++)
	{
		size_t	r1 = getRandomIntInRange<size_t>(0, POP.size()),
				r2 = getRandomIntInRange<size_t>(0, POP.size()),
				r3 = getRandomIntInRange<size_t>(0, POP.size()),
				r4 = getRandomIntInRange<size_t>(0, POP.size());

		// ensure i, r1, r2 are unique
		while (UNIQUE_5(i, r1, r2, r3, r4))
		{
			r1 = getRandomIntInRange<size_t>(0, POP.size());
			r2 = getRandomIntInRange<size_t>(0, POP.size());
		} // end while

		noise->gene[j] = (best(POP, j) + strat1(POP, F, j, r1, r2));
	} // end for

	return noise;
} // end method best_2_exp


Gene * DifferentialEvolution::rand_1(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rand_1_exp


Gene * DifferentialEvolution::rand_2(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rand_2_exp


Gene * DifferentialEvolution::rtb_1(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rtb_1_exp


double DifferentialEvolution::best(DE_Population & POP, const size_t j)
{
	return POP.best()->gene[j];
}

double DifferentialEvolution::strat1(DE_Population & POP, double F, std::size_t j, std::size_t r1, std::size_t r2)
{
	double temp = 0.0;

	temp = F * (POP[r1].gene[j] - POP[r2].gene[j]);

	return temp;
}

double DifferentialEvolution::start2(DE_Population & POP, double F, std::size_t j, std::size_t r1, std::size_t r2, std::size_t r3, std::size_t r4)
{
	double temp = 0.0;

	temp = F * (POP[r1].gene[j] + POP[r2].gene[j] - POP[r3].gene[j] - POP[r4].gene[j]);

	return temp;
}

double DifferentialEvolution::strat3(DE_Population & POP, double F, double lambda, std::size_t j, std::size_t i, std::size_t r1, std::size_t r2)
{
	double temp = 0.0;

	temp = lambda * (best(POP, j) - POP[i].gene[j]) + F * (POP[r1].gene[j] - POP[r2].gene[j]);

	return temp;
}







