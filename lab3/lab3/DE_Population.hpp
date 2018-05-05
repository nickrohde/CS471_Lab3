#pragma once

#ifndef _DE_POP_H
#define _DE_POP_H

#include "Population.hpp"

///<summary><see cref="Population"/> specific to Differential Evolution.</summary>
class DE_Population : public Population
{
public:
	// Constructors:
	/// <summary>Constructs an empty population.</summary>
	DE_Population(void) : Population() {}

	/// <summary>Constructs a new population with <paramref name="ui_SIZE"/> members, each of size <paramref name="ui_DIM"/>.</summary>
	/// <param name="ui_SIZE">The size of the population.</param>
	/// <param name="ui_DIM">The size of each gene in the population.</param>
	/// <param name="bounds">The min/max value that may be stored in a gene.</param>
	DE_Population(const std::size_t ui_SIZE, const std::size_t ui_DIM, const Bounds& bounds) : Population(ui_SIZE, ui_DIM, bounds) {}

	/// <summary>Constructs a new population that is a copy of the population <paramref name="other"/>.</summary>
	/// <param name="other">The population to copy.</param>
	DE_Population(const DE_Population& other);

	// Destructor:
	/// <summary>Releases all dynamic memory owned by this object.</summary>
	~DE_Population(void) {}

	// Operations: 
	/// <summary>Finds the fitness of all members of the population.</summary>
	/// <param name="f">The fitness function to evaluate the population on.</param>
	virtual void evaluateAll(fitnessFunction f)
	{
		for (auto& g : genes)
		{
			g.evaluate(f);
		} // end for
	} // end method evaluateAll
	
	// Iterators:
	/// <summary>Getter for an iterator to the start of the population.</summary>
	inline std::vector<Gene>::iterator begin(void);

	/// <summary>Getter for an iterator to the end of the population.</summary>
	inline std::vector<Gene>::iterator end(void);


}; // end Class DE_Population





#endif // !_DE_POP_H