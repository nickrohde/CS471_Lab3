#include "DE_Strategies.hpp"	// class header

using namespace std;


results_t* DifferentialEvolution::differentialEvolution(fitnessFunction f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const Crossing_Over_Info& CR_INFO, DE_Strategy t, size_t* numbers)
{
	// these two functions determine the strategy being used
	DE_Function genNoiseVector = nullptr;          // either RAND_1/2, BEST_1/2, or RTB_1
	Crossing_Over_Function crossingOver = nullptr; // either EXP or BIN

	differentialEvolutionHelper(t, &genNoiseVector, &crossingOver); // get the appropriate functions based on strategy to use

	DE_Population* current = new DE_Population(POP_INFO.ui_SIZE, POP_INFO.ui_GENE_DIM, BOUNDS);

	timePoint end = highRes_Clock::now();
	timePoint start = highRes_Clock::now();

	for (size_t gen = 0; gen < POP_INFO.ui_GENERATIONS; gen++)
	{
		DE_Population* new_pop = new DE_Population();

		current->evaluateAll(f);
		current->sort();

		for (size_t i = 0; i < POP_INFO.ui_SIZE; i++)
		{
			Gene * child = genNoiseVector(*current, i, BOUNDS, numbers);

			crossingOver(&((*current)[i]), child, POP_INFO.ui_GENE_DIM, CR_INFO.d_CROSSING_OVER_RATE);

			child->evaluate(f);

			if (child->d_fitness < (*current)[i].d_fitness)
			{
				(*new_pop) << child;
			} // end if
			else
			{
				(*new_pop) << &(*current)[i];
			} // end else

			delete child;
		} // end for

		delete current;
		current = new_pop;
	} // end for

	end = highRes_Clock::now();
	duration compute_time = std::chrono::duration_cast<duration>(end - start);

	current->evaluateAll(f);
	current->sort();

	results_t * res = new results_t();

	res->operator=(&(*current)[0]);
	res->d_avgTime = compute_time.count();

	delete current;

	return res;
} // end method differentialEvolution


void DifferentialEvolution::differentialEvolutionHelper(DE_Strategy t, DE_Function* f, Crossing_Over_Function* xf)
{
	// determine which strategy to use
	switch (t)
	{
	case DE_Strategy::DE_BEST_1_EXP:
		*f = best_1;
		*xf = crossingOverEXP;
		break;
	case DE_Strategy::DE_BEST_2_EXP:
		*f = best_2;
		*xf = crossingOverEXP;
		break;
	case DE_Strategy::DE_BEST_1_BIN:
		*f = best_1;
		*xf = crossingOverBIN;
		break;
	case DE_Strategy::DE_BEST_2_BIN:
		*f = best_1;
		*xf = crossingOverBIN;
		break;
	case DE_Strategy::DE_RAND_1_EXP:
		*f = rand_1;
		*xf = crossingOverEXP;
		break;
	case DE_Strategy::DE_RAND_2_EXP:
		*f = rand_2;
		*xf = crossingOverEXP;
		break;
	case DE_Strategy::DE_RAND_1_BIN:
		*f = rand_1;
		*xf = crossingOverBIN;
		break;
	case DE_Strategy::DE_RAND_2_BIN:
		*f = rand_2;
		*xf = crossingOverBIN;
		break;
	case DE_Strategy::DE_RTB_1_EXP: // this strategy slightly differs from DE_RTB_1_BIN, so we need to bind an argument to the function
		*f = std::bind(rtb_1, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, 1.0); // sign of lambda is +
		*xf = crossingOverEXP;
		break;
	case DE_Strategy::DE_RTB_1_BIN:		
		*f = std::bind(rtb_1, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, -1.0); // sign of lambda is -
		*xf = crossingOverBIN;
		break;
	} // end switch
} // end differentialEvolutionHelper


Gene * DifferentialEvolution::best_1(DE_Population& POP, std::size_t i, const Bounds& BOUNDS, size_t* numbers)
{
	const size_t RAND_NUMBERS = 2;

	size_t* rand_numbers = new size_t[RAND_NUMBERS]; // random indeces

	Gene* noise = new Gene();

	double F = getRandomRealInRange<double>(0.5, _ONE); // randomly pick scaling factor in the range [0.5,1] each iteration

	// setup noisy vector
	noise->gene.clear();
	noise->gene = vector<double>(POP[0].length());
	noise->ui_length = POP[0].length();

	// mutate noisy vector
	for (size_t j = 0; j < POP[0].length(); j++)
	{
		genPermutation(numbers, POP.ui_size, rand_numbers, RAND_NUMBERS, i); // generate a permutation for random indeces

		noise->gene[j] = (best(POP, j) + strat1(POP, F, j, rand_numbers[0], rand_numbers[1])); // apply strategy function

		// ensure the new value is not out-of-bounds
		while (noise->gene[j] > BOUNDS.d_max)
		{
			noise->gene[j] = noise->gene[j] - BOUNDS.d_max;
		} // end while
		while (noise->gene[j] < BOUNDS.d_min)
		{
			noise->gene[j] = noise->gene[j] - (BOUNDS.d_min - 0.1); // min can be 0
		} // end while
	} // end for

	delete[] rand_numbers;

	return noise;
} // end method best_1


Gene * DifferentialEvolution::best_2(DE_Population& POP, std::size_t i, const Bounds& BOUNDS, size_t * numbers)
{
	const size_t RAND_NUMBERS = 4;

	size_t* rand_numbers = new size_t[RAND_NUMBERS];

	Gene* noise = new Gene();

	double F = getRandomRealInRange<double>(0.5, _ONE);

	noise->gene.clear();
	noise->gene = vector<double>(POP[0].length());
	noise->ui_length = POP[0].length();


	for (size_t j = 0; j < POP[0].length(); j++)
	{
		genPermutation(numbers, POP.ui_size, rand_numbers, RAND_NUMBERS, i); // generate a permutation for random indeces

		noise->gene[j] = (best(POP, j) + strat2(POP, F, j, rand_numbers[0], rand_numbers[1], rand_numbers[2], rand_numbers[3]));

		// ensure the new value is not out-of-bounds
		while (noise->gene[j] > BOUNDS.d_max)
		{
			noise->gene[j] = noise->gene[j] - BOUNDS.d_max;
		} // end while
		while (noise->gene[j] < BOUNDS.d_min)
		{
			noise->gene[j] = noise->gene[j] - (BOUNDS.d_min - 0.1); // min can be 0
		} // end while
	} // end for

	delete[] rand_numbers;

	return noise;
} // end method best_2


Gene * DifferentialEvolution::rand_1(DE_Population& POP, std::size_t i, const Bounds& BOUNDS, size_t * numbers)
{
	const size_t RAND_NUMBERS = 3;

	size_t* rand_numbers = new size_t[RAND_NUMBERS];

	Gene* noise = new Gene();

	double F = getRandomRealInRange<double>(0.5, _ONE);

	noise->gene.clear();
	noise->gene = vector<double>(POP[0].length());
	noise->ui_length = POP[0].length();


	for (size_t j = 0; j < POP[0].length(); j++)
	{
		genPermutation(numbers, POP.ui_size, rand_numbers, RAND_NUMBERS, i); // generate a permutation for random indeces

		noise->gene[j] = (POP[rand_numbers[0]].gene[j] + strat1(POP, F, j, rand_numbers[1], rand_numbers[2]));

		// ensure the new value is not out-of-bounds
		while (noise->gene[j] > BOUNDS.d_max)
		{
			noise->gene[j] = noise->gene[j] - BOUNDS.d_max;
		} // end while
		while (noise->gene[j] < BOUNDS.d_min)
		{
			noise->gene[j] = noise->gene[j] - (BOUNDS.d_min - 0.1); // min can be 0
		} // end while
	} // end for

	delete[] rand_numbers;

	return noise;
} // end method rand_1


Gene * DifferentialEvolution::rand_2(DE_Population& POP, std::size_t i, const Bounds& BOUNDS, size_t * numbers)
{
	const size_t RAND_NUMBERS = 5;

	size_t* rand_numbers = new size_t[RAND_NUMBERS];

	Gene* noise = new Gene();

	double F = getRandomRealInRange<double>(0.5, _ONE);

	noise->gene.clear();
	noise->gene = vector<double>(POP[0].length());
	noise->ui_length = POP[0].length();


	for (size_t j = 0; j < POP[0].length(); j++)
	{
		genPermutation(numbers, POP.ui_size, rand_numbers, RAND_NUMBERS, i); // generate a permutation for random indeces

		noise->gene[j] = (POP[rand_numbers[0]].gene[j] + strat2(POP, F, j, rand_numbers[1], rand_numbers[2], rand_numbers[3], rand_numbers[4]));

		// ensure the new value is not out-of-bounds
		while (noise->gene[j] > BOUNDS.d_max)
		{
			noise->gene[j] = noise->gene[j] - BOUNDS.d_max;
		} // end while
		while (noise->gene[j] < BOUNDS.d_min)
		{
			noise->gene[j] = noise->gene[j] - (BOUNDS.d_min - 0.1); // min can be 0
		} // end while
	} // end for

	delete[] rand_numbers;

	return noise;
} // end method rand_2


Gene * DifferentialEvolution::rtb_1(DE_Population& POP, std::size_t i, const Bounds& BOUNDS, size_t * numbers, const double LAMBDA_SIGN)
{
	const size_t RAND_NUMBERS = 2;

	size_t* rand_numbers = new size_t[RAND_NUMBERS];

	Gene* noise = new Gene();

	double	F = getRandomRealInRange<double>(0.5, _ONE),
			lambda = (LAMBDA_SIGN) * (F / 2);

	noise->gene.clear();
	noise->gene = vector<double>(POP[0].length());
	noise->ui_length = POP[0].length();


	for (size_t j = 0; j < POP[0].length(); j++)
	{
		genPermutation(numbers, POP.ui_size, rand_numbers, RAND_NUMBERS, i); // generate a permutation for random indeces

		noise->gene[j] = (POP[i].gene[j] + strat3(POP, F, lambda, j, i, rand_numbers[0], rand_numbers[1]));

		// ensure the new value is not out-of-bounds
		while (noise->gene[j] > BOUNDS.d_max)
		{
			noise->gene[j] = noise->gene[j] - BOUNDS.d_max;
		} // end while
		while (noise->gene[j] < BOUNDS.d_min)
		{
			noise->gene[j] = noise->gene[j] - (BOUNDS.d_min - 0.1); // min can be 0
		} // end while
	} // end for

	delete[] rand_numbers;

	return noise;
} // end method rtb_1


void DifferentialEvolution::crossingOverBIN(Gene* parent, Gene* noise, const std::size_t N, const double CR)
{
	size_t	j = getRandomIntInRange<size_t>(0, N - 1),
			position = 0;

	while (position < N)
	{
		if (getRandomRealInRange<double>(0.0, _ONE) < CR)
		{
			noise->gene[j] = parent->gene[j];
		} // end if

		j = ((j + 1) % N);
		position++;
	} // end while
} // end method crossingOverBIN


void DifferentialEvolution::crossingOverEXP(Gene* parent, Gene* noise, const std::size_t N, const double CR)
{
	size_t	j = getRandomIntInRange<size_t>(0, N - 1),
			position = 0;

	do
	{
		noise->gene[j] = parent->gene[j];

		j = ((j + 1) % N);
		position++;
	} while ((getRandomRealInRange<double>(0.0, _ONE) < CR) && position < N);
} // end method crossingOverEXP


inline double DifferentialEvolution::best(DE_Population & POP, const size_t j)
{
	return POP.best()->gene[j];
} // end method best


inline double DifferentialEvolution::strat1(DE_Population & POP, double F, std::size_t j, std::size_t r1, std::size_t r2)
{
	return (F * (POP[r1].gene[j] - POP[r2].gene[j]));
} // end method strat1


inline double DifferentialEvolution::strat2(DE_Population & POP, double F, std::size_t j, std::size_t r1, std::size_t r2, std::size_t r3, std::size_t r4)
{
	return (F * (POP[r1].gene[j] + POP[r2].gene[j] - POP[r3].gene[j] - POP[r4].gene[j]));
} // end method strat2


inline double DifferentialEvolution::strat3(DE_Population & POP, double F, double lambda, std::size_t j, std::size_t i, std::size_t r1, std::size_t r2)
{
	return (lambda * (best(POP, j) - POP[i].gene[j]) + F * (POP[r1].gene[j] - POP[r2].gene[j]));
} // end method strat3







