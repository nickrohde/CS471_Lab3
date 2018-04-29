#pragma once

#ifndef _GENE_H
#define _GENE_H

#include <vector>
#include <iostream>
#include "utility.hpp"

class Gene;

///<summary>Stores the offspring after a crossover.</summary>
struct Offspring
{
	/// <summary>Vector containing the genes that are offsprings of the parents.</summary>
	std::vector<Gene> offsprings;
}; // end Struct Offspring


class Gene
{
public:
	// Constructors:
	Gene(const std::size_t ui_SIZE, const double d_MIN, const double d_MAX);

	// Destructor:
	~Gene(void);

	// Operations:
	void mutate(const double d_MR);

	// Getters:
	inline std::size_t length(void) const;
	
	// Operators:
	double& operator[](size_t i);
	double operator[](size_t i) const;

	friend std::ostream& operator<<(std::ostream& stream, const Gene& gene);

private:
	double	d_min, 
			d_max;

	std::vector<double> gene;
	std::size_t	ui_length;

}; // end Class Gene






#endif // !_GENOME_H
