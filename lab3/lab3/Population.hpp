#pragma once

#ifndef _POPULATION_H
#define _POPULATION_H

#include <vector>
#include "Gene.hpp"
#include <algorithm>

typedef std::vector<Gene> GenePool;

///<summary>Stores the genetic information of a population.</summary>
class Population
{
public:
	// Constructors:
	/// <summary>Constructs an empty population for genes of length <paramref name="ui_DIM"/>.</summary>
	/// <param name="ui_DIM">The size of each gene in the population.</param>
	Population(const std::size_t ui_DIM);

	/// <summary>Constructs a new population with <paramref name="ui_SIZE"/> members, each of size <paramref name="ui_DIM"/>.</summary>
	/// <param name="ui_SIZE">The size of the population.</param>
	/// <param name="ui_DIM">The size of each gene in the population.</param>
	/// <param name="bounds">The min/max value that may be stored in a gene.</param>
	Population(const std::size_t ui_SIZE, const std::size_t ui_DIM, const Bounds bounds);

	/// <summary>Constructs a new population that is a copy of the population <paramref name="other"/>.</summary>
	/// <param name="other">The population to copy.</param>
	Population(const Population& other);

	// Destructor:
	/// <summary>Releases all dynamic memory owned by this object.</summary>
	~Population(void) {}

	// Operations:
	/// <summary>Finds the fitness of all members of the population and calculates the total fitness of the population.</summary>
	/// <param name="f">The fitness function to evaluate the population on.</param>
	void evaluateAll(fitnessFunction f);

	// Getters:
	/// <summary>Getter for the size of the population.</summary>
	/// <returns>The size of this population.</returns>
	inline std::size_t size(void) const;

	/// <summary>Getter for the total fitness of the population.</summary>
	/// <returns>The total fitness of this population.</returns>
	inline double totalFitness(void) const;

	// Operators:
	/// <summary>Accessor for the member at index <paramref name="i"/>.</summary>
	/// <param name="i">The 0-based index to access.</param>
	/// <returns>A reference to the member at index i.</returns>
	/// <exception name="std::out_of_range">Thrown if <paramref name="i"/> is larger than the size of the population.</exception>
	inline Gene& operator[](const std::size_t i);

	/// <summary>Accessor for the member at index <paramref name="i"/>.</summary>
	/// <param name="i">The 0-based index to access.</param>
	/// <returns>A copy of the member at index i.</returns>
	/// <exception name="std::out_of_range">Thrown if <paramref name="i"/> is larger than the size of the population.</exception>
	inline Gene operator[](const std::size_t i) const;

	/// <summary>Adds the gene <paramref name="newGene"/> to this population.</summary>
	/// <param name="newGene">The new gene that will be added to this population.</param>
	/// <remarks>The gene to be added must be compatible, i.e. of the same length as the genes already in this population.</remarks>
	/// <exception name="std::invalid_argument">Thrown if <paramref name="newGene"/> is not the same length as all other genes in this population.</exception>
	inline void operator+=(Gene& newGene);

	/// <summary>Adds the genes <paramref name="newGenes"/> to this population.</summary>
	/// <param name="newGene">The new genes that will be added to this population.</param>
	/// <remarks>All genes to be added must be compatible, i.e. of the same length as the genes already in this population.</remarks>
	/// <exception name="std::invalid_argument">Thrown if any gene in <paramref name="newGenes"/> is not the same length as all other genes in this population.</exception>
	inline void operator+=(Offspring& newGenes);

	/// <summary>Inserts the contents of <paramref name="pop"/> into the <paramref name="stream"/>.</summary>
	/// <param name="stream">The stream to insert this population into.</param>
	/// <param name="pop">The population to be inserted.</param>
	/// <returns>The stream with the contents of <paramref name="pop"/> added to the end.</returns>
	friend std::ostream& operator<<(std::ostream& stream, const Population& pop);


	// Static Methods:
	// Operations:
	/// <summary>Sorts the population <paramref name="pop"/> in ascending order.</summary>
	inline void sort(void);

private:
	/// <summary>The gene pool of this population.</summary>
	GenePool genes;

	/// <summary>The size of this population.</summary>
	std::size_t ui_size;

	/// <summary>The total fitness of all members of this population</summary>
	double d_totalFitness;
}; // end Class Population

#endif