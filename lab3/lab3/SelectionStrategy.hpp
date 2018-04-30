#pragma once

#ifndef _SELECTION_STRAT_H
#define _SELECTION_STRAT_H

#include "Population.hpp"

class Selection_Strategy
{
public:
	virtual Gene* selectParent(const Population& pop) = 0;
};

class RouletteWheel : public Selection_Strategy
{
	virtual Gene* selectParent(const Population& pop);
};



#endif // !_SELECTION_STRAT_H
