#pragma once

#ifndef _DE_STRATS_H
#define _DE_STRATS_H

#include "DE_Population.hpp"
#include "results.hpp"
#include <functional>


///<summary>Improves readibility and is more convenient.</summary>
typedef std::function<Gene*(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO)> DE_Function;

///<summary>Enum for the 10 Differential Evolution Strategies.</summary>
enum DE_Strategy
{
	DE_BEST_1_EXP,
	DE_BEST_2_EXP,

	DE_BEST_1_BIN,
	DE_BEST_2_BIN,

	DE_RAND_1_EXP,
	DE_RAND_2_EXP,

	DE_RAND_1_BIN,
	DE_RAND_2_BIN,

	DE_RTB_1_EXP,
	DE_RTB_1_BIN,
}; // end enum DE_Strategy

/// <summary>
///			 Finds the optimal solution to <paramref name="f"/> by randomly generating an initial population, and then executing the specified DE strategy
///			 to optimize this population.
/// </summary>
/// <param name="f">The fitness function to minimize.</param>
/// <param name="POP_INFO">Info regarding population, s.a. size, generations, etc.</param>
/// <param name="BOUNDS">Problem bounds of <paramref name="f"/>.</param>
/// <param name="MUT_INFO">Info regarding mutations, s.a. rate, etc.</param>
/// <param name="CR_INFO">Info regarding crossing over, s.a. rate, etc.</param>
/// <param name="t">The type of strategy to use.</param>
/// <returns>The optimal solution to <paramref name="f"/> found using the DE strategy <paramref name="t"/>.</returns>
results_t* differentialEvolution(fitnessFunction f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const Mutation_Info& MUT_INFO, const Crossing_Over_Info& CR_INFO, DE_Strategy t);

/// <summary>Creates a pointer to the <see cref="DE_Function"/> (strategy) of type <paramref name="t"/>.</summary>
/// <returns>A pointer to the requested <see cref="DE_Function"/>.</returns>
DE_Function differentialEvolutionHelper(DE_Strategy t);


Gene* best_1_exp(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO);
Gene* best_2_exp(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO);

Gene* best_1_bin(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO);
Gene* best_2_bin(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO);

Gene* rand_1_exp(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO);
Gene* rand_2_exp(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO);

Gene* rand_1_bin(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO);
Gene* rand_2_bin(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO);

Gene* rtb_1_exp(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO);
Gene* rtb_1_bin(const DE_Population& POP, const Bounds& BOUNDS, const DE_Info& DE_INFO);



#endif // !_DE_STRATS_H
