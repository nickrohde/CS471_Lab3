#pragma once

#ifndef _TEST_H
#define _TEST_H
#include <initializer_list> // variadic template
#include "functions.hpp"    // cost functions
#include "Containers.hpp"
#include "results.hpp"

#define SHEKEL_OUTER_SIZE 30 // size of outer array used by shekel's foxholes
#define SHEKEL_INNER_SIZE 10 // size of inner array used by shekel's foxholes
#define NUMBER_FUNCTIONS  15 // number of cost function

typedef std::function<double(const std::vector<double>*)> fitnessFunction;

/// <summary>Class that handles testing of the optimization strategies.</summary>
class Test
{
public:
	/// <summary>Default constructor, sets all variables to a default.</summary>
	Test(void);

	/// <summary>Constructor taking 4 arguements.</summary>
	/// <param name="ui_dimMin">Starting dimension for tests (inclusive; must be positive integer and strictly smaller than <paramref name="ui_dimMax"/>).</param>
	/// <param name="ui_dimMax">Ending dimension for tests (inclusive; must be positive integer and strictly greater than <paramref name="ui_dimMin"/>).</param>
	/// <param name="ui_dimDelta">Dimension increase step size (must be positive integer).</param>
	/// <param name="b_storeData">Whether or not to generate data files.</param>
	/// <param name="ui_generations">Number of generations to run DE/GA.</param>
	Test(std::size_t ui_dimMin, std::size_t ui_dimMax, std::size_t ui_dimDelta, bool b_storeData, std::size_t ui_generations);

	/// <summary>Destructor. Frees all dynamic memory beloging to this object.</summary>
	~Test(void);

	/// <summary>Runs the given DE strategy to optimize all cost functions.</summary>
	/// <param name="ui_iterations">Number of iterations to run DE.</param>
	/// <param name="CR">Crossover rate.</param>
	/// <param name="strat">DE strategy to use.</param>
	void RunDE(size_t ui_iterations, double CR, size_t strat);

	/// <summary>Runs GA to optimize all cost functions.</summary>
	/// <param name="ui_iterations">Number of iterations to run DE.</param>
	/// <param name="MR">Mutation rate.</param>
	/// <param name="MRg">Mutation Range.</param>
	/// <param name="MP">Mutation precision.</param>
	/// <param name="CP">Crossover points.</param>
	/// <param name="CR">Crossover rate.</param>
	/// <param name="ER">Elitism rate.</param>
	void RunGA(size_t ui_iterations, double MR, double MRg, double MP, size_t CP, double CR, double ER);

#pragma region Private
private:
	// Member Constants:
	/// <summary>Number of iterations that the shekel's foxhole inner loop will execute.</summary>
	const std::size_t ui_SHEKEL_M = 10;

	// Member Variables:
	/// <summary>Array containing the bounds of all 15 cost functions.</summary>
	Bounds * da_ranges;
	/// <summary>Shekel's foxholes arguements.</summary>
	double ** da_A;

	/// <summary>Dimension info.</summary>
	std::size_t	ui_minDimensions,
				ui_maxDimensions,
				ui_dimensionDelta,
				ui_generations;

	/// <summary>Whether or not to generate data file.</summary>
	bool b_storeData;

	/// <summary>Used for timing tests.</summary>
	timePoint	compute_start,
				compute_end;
	duration	time_to_compute;

	/// <summary>Vector containing pointers to the cost functions.</summary>
	std::vector<fitnessFunction> fitnessFunctions;


	// Private Functions:
	/// <summary>Generates the matrix for shekel's foxholes.</summary>
	/// <param name="da_A">A valid pointer to an array of 30 uninitialized double pointers.</param>
	/// <remarks>This function is only there to remove some code from the constructor, it is inline and will simply be placed in the constructor by the compiler.</remarks>
	void makeMatrix(double**& da_A);

	/// <summary>Generates the matrix containing the ranges for all cost functions.</summary>
	/// <param name="da_A">A valid pointer to an array of 15 uninitialized double pointers.</param>
	/// <remarks>This function is only there to remove some code from the constructor, it is inline and will simply be placed in the constructor by the compiler.</remarks>
	void makeRanges(Bounds*& da_ranges);

	/// <summary>Generates data file with test data.</summary>
	/// <param name="s_name">Name of the file to dump the data into.</param>
	/// <param name="res">A pointer to a results_t object containing the data to dump.</param>
	/// <remarks>This function is only called if b_storeData is set to true. The files created tend to be very large.</remarks>
	void dumpDataToFile(std::string s_name, results_t* res);

	/// <summary>Generates results file with test results.</summary>
	/// <param name="res">A pointer to a results_t object containing the test results.</param>
	/// <remarks>This function only writes the optimal point and solution to the file, all other data is ignored.</remarks>
	void writeResultsToFile(results_t* res);

	/// <summary>Generates a file name. Name will be generated as "data_[<paramref name="ui_dim"/>]_f[<paramref name="i_functionNumber"/>]".</summary>
	/// <param name="ui_dim">Dimension to insert into the name.</param>
	/// <param name="i_functionNumber">Function number to insert into the name.</param>
	std::string makeFileName(std::size_t ui_dim, int i_functionNumber);

#pragma endregion

}; // end Class Test

#endif // !_TEST_H
