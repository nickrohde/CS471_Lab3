#include "DE_Strategies.hpp"

using namespace std;


results_t* differentialEvolution(fitnessFunction f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const Mutation_Info& MUT_INFO, const Crossing_Over_Info& CR_INFO, DE_Strategy t)
{
	DE_Function genNoiseVector = differentialEvolutionHelper(t);

	for (size_t gen = 0; gen < POP_INFO.ui_GENERATIONS; gen++)
	{




	} // end for

	return nullptr;
} // end method differentialEvolution


DE_Function differentialEvolutionHelper(DE_Strategy t)
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


Gene * best_1_exp(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)
{
	//Gene* best = POP.best();


	size_t	j = getRandomIntInRange<size_t>(0, POP[0].length()), // random starting index
			position = 0; // position in the circur vector (counter)

	do
	{
		

	} while (getRandomRealInRange<double>(0, _ONE) < DE_INFO.d_CR && position < POP[0].length());



	throw std::logic_error("Not Implemented");
} // end method best_1_exp


Gene * best_2_exp(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method best_2_exp


Gene * best_1_bin(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method best_1_bin


Gene * best_2_bin(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method best_2_bin


Gene * rand_1_exp(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rand_1_exp


Gene * rand_2_exp(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rand_2_exp


Gene * rand_1_bin(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rand_1_bin


Gene * rand_2_bin(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rand_2_bin


Gene * rtb_1_exp(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rtb_1_exp


Gene * rtb_1_bin(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rtb_1_bin




