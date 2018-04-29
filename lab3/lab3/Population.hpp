#pragma once

#ifndef _POPULATION_H
#define _POPULATION_H

#include <vector>
#include "Gene.hpp"

typedef std::vector<Gene> Matrix;


class Population
{
public:

	Population(void);
	Population(const std::size_t ui_DIM, const std::size_t ui_NUM_MEBERS);
	~Population(void);

	Gene getMember(size_t ui_i);




private:
	Matrix		m_genomes;

	std::size_t ui_dim,
				ui_numMembers;


};




#endif