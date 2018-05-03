#pragma once

#ifndef _DE_POP_H
#define _DE_POP_H

#include "Population.hpp"

///<summary><see cref="Population"/> specific to Differential Evolution.</summary>
class DE_Population : public Population
{
	/// <summary>Finds the fitness of all members of the population.</summary>
	/// <param name="f">The fitness function to evaluate the population on.</param>
	virtual void evaluateAll(fitnessFunction f);
	
	/// <summary>Getter for an iterator to the start of the population.</summary>
	inline std::vector<Gene>::iterator begin(void);

	/// <summary>Getter for an iterator to the end of the population.</summary>
	inline std::vector<Gene>::iterator end(void);

	


}; // end Class DE_Population





#endif // !_DE_POP_H