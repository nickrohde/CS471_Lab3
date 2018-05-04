#include "DE_Strategies.hpp"

using namespace std;


results_t* differentialEvolution(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO, DE_Strategy t)
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

	return g(f, POP_INFO, BOUNDS, MUT_INFO, CR_INFO);
} // end method differentialEvolution


results_t* best_1_exp(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method best_1_exp


results_t* best_2_exp(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method best_2_exp


results_t* best_1_bin(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method best_1_bin


results_t* best_2_bin(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method best_2_bin


results_t* rand_1_exp(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rand_1_exp


results_t* rand_2_exp(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rand_2_exp


results_t* rand_1_bin(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rand_1_bin


results_t* rand_2_bin(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rand_2_bin


results_t* rtb_1_exp(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rtb_1_exp


results_t* rtb_1_bin(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO)
{
	throw std::logic_error("Not Implemented");
} // end method rtb_1_bin


