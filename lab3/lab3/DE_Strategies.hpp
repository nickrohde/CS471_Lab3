#pragma once

#ifndef _DE_STRATS_H
#define _DE_STRATS_H

#include "MasterInclude.hpp"
#include "results.hpp"
#include "Containers.hpp"
#include "Gene.hpp"
#include "DE_Population.hpp"


///<summary>Improves readibility of mutation strategy functions.</summary>
typedef std::function<Gene*(DE_Population& POP, std::size_t i, const Bounds&, size_t*)> DE_Function;

///<summary>Improves readibility of crossing over strategy functions.</summary>
typedef std::function<void(Gene*, Gene*, const std::size_t, const double)> Crossing_Over_Function;

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


/// <summary>Wrapper class for DE, allows all DE methods to have friendship relationship with Gene.</summary>
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
	/// <param name="CR_INFO">Info regarding crossing over, s.a. rate, etc.</param>
	/// <param name="t">The type of strategy to use.</param>
	/// <param name="numbers">Array containing valid indeces for generating permutations.</param>
	/// <returns>The optimal solution to <paramref name="f"/> found using the DE strategy <paramref name="t"/>.</returns>
	static results_t* differentialEvolution(fitnessFunction f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const Crossing_Over_Info& CR_INFO, DE_Strategy t, std::size_t* numbers);

	/// <summary>Determines the appropriate mutation and crossing over functions to use for strategy <paramref name="t"/>.</summary>
	/// <param name="t">Type of strategy to use.</param>
	/// <param name="f">Pointer to <see cref="DE_Function"/> object that will be assigned an appropriate value according to <paramref name="t"/>.</param>
	/// <param name="xf">Pointer to <see cref="Crossing_Over_Function"/> object that will be assigned an appropriate value according to <paramref name="t"/>.</param>
	static void differentialEvolutionHelper(DE_Strategy t, DE_Function* f, Crossing_Over_Function* xf);

	/// <summary>Creates a noise vector according to BEST_1 strategy.</summary>
	/// <param name="POP">The population.</param>
	/// <param name="i">Current individual being considered.</param>
	/// <param name="BOUNDS">Problem bounds.</param>
	/// <param name="numbers">Array containing valid indeces for generating permutations.</param>
	/// <returns>A pointer to a Gene object containing the noise vector.</returns>
	static Gene* best_1(DE_Population& POP, std::size_t i, const Bounds& BOUNDS, size_t * numbers);

	/// <summary>Creates a noise vector according to BEST_2 strategy.</summary>
	/// <param name="POP">The population.</param>
	/// <param name="i">Current individual being considered.</param>
	/// <param name="BOUNDS">Problem bounds.</param>
	/// <param name="numbers">Array containing valid indeces for generating permutations.</param>
	/// <returns>A pointer to a Gene object containing the noise vector.</returns>
	static Gene* best_2(DE_Population& POP, std::size_t i, const Bounds& BOUNDS, size_t * numbers);

	/// <summary>Creates a noise vector according to RAND_1 strategy.</summary>
	/// <param name="POP">The population.</param>
	/// <param name="i">Current individual being considered.</param>
	/// <param name="BOUNDS">Problem bounds.</param>
	/// <param name="numbers">Array containing valid indeces for generating permutations.</param>
	/// <returns>A pointer to a Gene object containing the noise vector.</returns>
	static Gene* rand_1(DE_Population& POP, std::size_t i, const Bounds& BOUNDS, size_t * numbers);

	/// <summary>Creates a noise vector according to RAND_2 strategy.</summary>
	/// <param name="POP">The population.</param>
	/// <param name="i">Current individual being considered.</param>
	/// <param name="BOUNDS">Problem bounds.</param>
	/// <param name="numbers">Array containing valid indeces for generating permutations.</param>
	/// <returns>A pointer to a Gene object containing the noise vector.</returns>
	static Gene* rand_2(DE_Population& POP, std::size_t i, const Bounds& BOUNDS, size_t * numbers);

	/// <summary>Creates a noise vector according to RAND_TO_BEST_1 strategy.</summary>
	/// <param name="POP">The population.</param>
	/// <param name="i">Current individual being considered.</param>
	/// <param name="BOUNDS">Problem bounds.</param>
	/// <param name="numbers">Array containing valid indeces for generating permutations.</param>
	/// <returns>A pointer to a Gene object containing the noise vector.</returns>
	static Gene* rtb_1(DE_Population& POP, std::size_t i, const Bounds& BOUNDS, size_t * numbers, const double LAMBDA_SIGN);

	/// <summary>Performs crossing over between <paramref name="parent"/> and <paramref name="noise"/> according to EXP strategy.</summary>
	/// <param name="parent">The parent of the <paramref name="noise"/> gene.</param>
	/// <param name="noise">The noise vector currently under consideration.</param>
	/// <param name="N">Population size.</param>
	/// <param name="CR">Crossing-over rate.</param>
	static void crossingOverEXP(Gene* parent, Gene* noise, const std::size_t N, const double CR);

	/// <summary>Performs crossing over between <paramref name="parent"/> and <paramref name="noise"/> according to BIN strategy.</summary>
	/// <param name="parent">The parent of the <paramref name="noise"/> gene.</param>
	/// <param name="noise">The noise vector currently under consideration.</param>
	/// <param name="N">Population size.</param>
	/// <param name="CR">Crossing-over rate.</param>
	static void crossingOverBIN(Gene* parent, Gene* noise, const std::size_t N, const double CR);

	/// <summary>Finds the value of the <paramref name="j"/>th component of the best member of <paramref name="POP"/>.</summary>
	/// <param name="POP">The population.</param>
	/// <param name="j">The current component being considered.</param>
	/// <returns>The value of <paramref name="j"/>th component of the best member of <paramref name="POP"/>.</returns>
	static inline double best(DE_Population& POP, const std::size_t j);

	/// <summary>Generates a noise component according to strategy 1.</summary>
	/// <param name="POP">The population.</param>
	/// <param name="F">Scaling factor.</param>
	/// <param name="j">The current component being considered.</param>
	/// <param name="r1">Random index.</param>
	/// <param name="r2">Random index.</param>
	/// <returns>The value of <paramref name="j"/>th component of the best member of <paramref name="POP"/>.</returns>
	static inline double strat1(DE_Population& POP, double F, std::size_t j, std::size_t r1, std::size_t r2);

	/// <summary>Generates a noise component according to strategy 2.</summary>
	/// <param name="POP">The population.</param>
	/// <param name="F">Scaling factor.</param>
	/// <param name="j">The current component being considered.</param>
	/// <param name="r1">Random index.</param>
	/// <param name="r2">Random index.</param>
	/// <param name="r3">Random index.</param>
	/// <param name="r4">Random index.</param>
	/// <returns>The value of <paramref name="j"/>th component of the best member of <paramref name="POP"/>.</returns>
	static inline double strat2(DE_Population& POP, double F, std::size_t j, std::size_t r1, std::size_t r2, std::size_t r3, std::size_t r4);

	/// <summary>Generates a noise component according to strategy rand-to-best 1.</summary>
	/// <param name="POP">The population.</param>
	/// <param name="F">Scaling factor.</param>
	/// <param name="lambda">Scaling factor.</param>
	/// <param name="j">The current component being considered.</param>
	/// <param name="i">Parent index.</param>
	/// <param name="r1">Random index.</param>
	/// <param name="r2">Random index.</param>
	/// <returns>The value of <paramref name="j"/>th component of the best member of <paramref name="POP"/>.</returns>
	static inline double strat3(DE_Population& POP, double F, double lambda, std::size_t j, std::size_t i, std::size_t r1, std::size_t r2);
}; // end Class DE_Strategies


#endif // !_DE_STRATS_H
