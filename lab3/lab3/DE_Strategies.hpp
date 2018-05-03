#pragma once

#ifndef _DE_STRATS_H
#define _DE_STRATS_H

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






#endif // !_DE_STRATS_H
