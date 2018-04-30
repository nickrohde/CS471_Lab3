#pragma once

#ifndef _GENETIC_ALG_H
#define _GENETIC_ALG_H

#include "Population.hpp"
#include "results.hpp"

/// <summary>
///			 Finds the optimal solution to <paramref name="f"/> by generating an initial population and then generating new populations 
///			 based on the previous one until a certain number of generations have been created.
/// </summary>
/// <param name="f">The cost function to optimize.</param>
/// <param name="POP_INFO">Various info about the population, such as size, gene size, crossing-over rate, etc.</param>
/// <param name="BOUNDS">The upper and lower problem bounds.</param>
/// <param name="MUT_INFO">The rate, precision, and range at which mutations occur.</param>
/// <returns>The optimal solution to <paramref name="f"/> found after <paramref name="ui_GENERATIONS"/> generations.</returns>
results_t* geneticAlgorithm(fitnessFunction f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const Mutation_Info& MUT_INFO);



#endif 
