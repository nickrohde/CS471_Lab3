#pragma once

#ifndef _DE_STRATS_H
#define _DE_STRATS_H

#include "DE_Population.hpp"

typedef function <results_t*(fitnessFunction, const Population_Info, const Bounds, const Mutation_Info, const Crossing_Over_Info)> DE_Function;

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
results_t* differentialEvolution(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO, DE_Strategy t);

results_t* best_1_exp(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO);
results_t* best_2_exp(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO);

results_t* best_1_bin(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO);
results_t* best_2_bin(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO);

results_t* rand_1_exp(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO);
results_t* rand_2_exp(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO);

results_t* rand_1_bin(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO);
results_t* rand_2_bin(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO);

results_t* rtb_1_exp(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO);
results_t* rtb_1_bin(fitnessFunction f, const Population_Info POP_INFO, const Bounds BOUNDS, const Mutation_Info MUT_INFO, const Crossing_Over_Info CR_INFO);



#endif // !_DE_STRATS_H
