#pragma once

#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "Gene.hpp"


///<summary>Stores the offspring after a crossover.</summary>
struct Offspring
{
	/// <summary>Copy assignment.</summary>
	/// <param name="OTHER">The object to copy.</param>
	inline void operator=(const Offspring& OTHER);

	/// <summary>Vector containing the genes that are offsprings of the parents.</summary>
	std::vector<Gene> offsprings;
}; // end Struct Offspring


/// <summary>Stores the problem bounds.</summary>
struct Bounds
{
	/// <summary>Lower bound.</summary>
	double	d_min, 
	/// <summary>Upper bound.</summary>
			d_max;

	/// <summary>Default constructor, zeros all members.</summary>
	Bounds(void);

	/// <summary>Creates a bounds structure with the given upper and lower bounds.</summary>
	/// <param name="min">Lower bound.</param>
	/// <param name="max">Upper bound.</param>
	Bounds(const double min, const double max);

	/// <summary>Copy constructor.</summary>
	/// <param name="OTHER">The Bounds to copy into this.</param>
	Bounds(const Bounds& OTHER);

	/// <summary>Copy assignment.</summary>
	/// <param name="OTHER">The object to copy.</param>
	void operator=(const Bounds& OTHER);
}; // end Struct Bounds


/// <summary>Stores the mutation information.</summary>
struct Mutation_Info
{
	/// <summary>Default constructor, zeros all members.</summary>
	Mutation_Info(void);

	/// <summary>Constructs a new structure containing the given values.</summary>
	/// <param name="rate">The rate at which mutations occur.</param>
	/// <param name="range">The range for mutations.</param>
	/// <param name="prec">The precision of mutations.</param>
	Mutation_Info(double rate, double range, double prec);

	/// <summary>Copy constructor.</summary>
	/// <param name="OTHER">The Mutation_Info to copy into this.</param>
	Mutation_Info(const Mutation_Info& OTHER);

	/// <summary>Copy assignment.</summary>
	/// <param name="OTHER">The object to copy.</param>
	void operator=(const Mutation_Info& OTHER);

	double	d_rate,
			d_range,
			d_precision;
}; // end struct Mutation_Info


   /// <summary>Stores the crossing-over information.</summary>
struct Crossing_Over_Info
{
	/// <summary>Default constructor, zeros all members.</summary>
	Crossing_Over_Info(void);

	/// <summary>Constructs a structure with the given values.</summary>
	/// <param name="offsprings">Number of offsprings to generate per couple.</param>
	/// <param name="points">Number of crossing-points to generate.</param>
	/// <param name="rate">Chance of crossing-over to occur.</param>
	Crossing_Over_Info(std::size_t offsprings, std::size_t points, double rate);

	/// <summary>Copy assignment.</summary>
	/// <param name="OTHER">The object to copy.</param>
	void operator=(const Crossing_Over_Info& OTHER);

	/// <summary>The number of offspring for each couple.</summary>
	std::size_t	ui_NUM_OFFSPRING,

	/// <summary>The number of cross-over points to generate.</summary>
				ui_CROSSING_OVER_POINTS;

	/// <summary>The chance for crossing-over to occur.</summary>
	double		d_CROSSING_OVER_RATE;
};


/// <summary>Stores the population information.</summary>
struct Population_Info
{
	/// <summary>Default constructor, zeros all members.</summary>
	Population_Info(void);

	/// <summary>Constructs a structure with the given values.</summary>
	/// <param name="size">Size of population.</param>
	/// <param name="dim">Length of genes.</param>
	/// <param name="gen">Number of generations to run.</param>
	/// <param name="ER">Elitism rate.</param>
	/// <param name="allow_growth">(Optional) Whether or not the population can grow. DEFAULT: false</param>
	/// <param name="growthFactor">(Optional) The rate at which growth occurs if it is allowed. DEFAULT: 0.0</param>
	Population_Info(std::size_t size, std::size_t dim, std::size_t gen, double ER, bool allow_growth = false, double growthFactor = 0.0);

	/// <summary>Copy assignment.</summary>
	/// <param name="OTHER">The object to copy.</param>
	void operator=(const Population_Info& OTHER);

	/// <summary>Size of the population.</summary>
	std::size_t ui_SIZE,

	/// <summary>Gene length for population members.</summary>
				ui_GENE_DIM,

	/// <summary>Number of generations to run.</summary>
				ui_GENERATIONS;

	/// <summary>The elitism rate.</summary>
	double		d_ELITISM_RATE,

	/// <summary>When <see cref="b_ALLOW_POP_GROWTH"/> is set, this is the maximum growth for the population per generation. Otherwise this is ignored.</summary>
				d_GROWTH_FACTOR;

	/// <summary>Whether or not the population can grow.</summary>
	bool		b_ALLOW_POP_GROWTH;
}; // end Struct Population Info

#endif // !_CONTAINER_H