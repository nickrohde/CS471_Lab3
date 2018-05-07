#pragma once

#ifndef _DE_STRATS_H
#define _DE_STRATS_H

#include "DE_Population.hpp"
#include "results.hpp"
#include <functional>

#define UNIQUE_4(a,b,c,d)   ((a^b) && (a^c) && (a^d) && (b^c) && (b^d) && (c^d))
#define UNIQUE_5(a,b,c,d,e) ((a^b) && (a^c) && (a^d) && (a^e) && (b^c) && (b^d) && (b^e) && (c^d) && (c^e) && (d^e))
#define UNIQUE_6(a,b,c,d,e,f) (UNIQUE_5(a,b,c,d,e) && (a^f) && (b^f) && (c^f) && (d^f) && (e^f))


///<summary>Improves readibility and is more convenient.</summary>
typedef std::function<Gene*(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO)> DE_Function;

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


class DifferentialEvolution
{
public:
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
	static results_t* differentialEvolution(fitnessFunction f, const DE_Info& DE_INFO, const Population_Info& POP_INFO, const Bounds& BOUNDS, const Mutation_Info& MUT_INFO, const Crossing_Over_Info& CR_INFO, DE_Strategy t);

	/// <summary>Creates a pointer to the <see cref="DE_Function"/> (strategy) of type <paramref name="t"/>.</summary>
	/// <returns>A pointer to the requested <see cref="DE_Function"/>.</returns>
	static DE_Function differentialEvolutionHelper(DE_Strategy t);


	static Gene* best_1(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO);
	static Gene* best_2(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO);

	static Gene* rand_1(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO);
	static Gene* rand_2(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO);

	static Gene* rtb_1(DE_Population& POP, std::size_t i, const DE_Info& DE_INFO);

	static Gene* crossingOverEXP(DE_Population& POP, Gene* parent, Gene* noise);
	static Gene* crossingOverBIN(DE_Population& POP, Gene* parent, Gene* noise);

	static double best(DE_Population& POP, const std::size_t j);

	static double strat1(DE_Population& POP, double F, std::size_t j, std::size_t r1, std::size_t r2);

	static double start2(DE_Population& POP, double F, std::size_t j, std::size_t r1, std::size_t r2, std::size_t r3, std::size_t r4);

	static double strat3(DE_Population& POP, double F, double lambda, std::size_t j, std::size_t i, std::size_t r1, std::size_t r2);

};


#endif // !_DE_STRATS_H
