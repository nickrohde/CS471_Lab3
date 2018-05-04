#include "Gene.hpp"

using namespace std;


Gene::Gene(const size_t ui_SIZE, const Bounds BOUNDS)
{
	ui_length = ui_SIZE;
	bounds = BOUNDS;

	for (size_t i = 0; i < ui_length; i++)
	{
		gene.push_back(getRandomRealInRange(bounds.d_min, bounds.d_max));
	} // end for
} // end Constructor 3


Gene::Gene(const Gene& PARENT_A, const Gene& PARENT_B, std::size_t ui_CO_POINTS)
{
	ui_length = PARENT_A.length();
	bounds = PARENT_A.bounds;

	vector<size_t> indeces;

	for (size_t i = 0; i < ui_CO_POINTS; i++)
	{
		indeces.push_back(getRandomIntInRange<size_t>(0, PARENT_A.length()));
	} // end for

	// order cross over points
	std::sort(indeces.begin(), indeces.end());

	recombine(PARENT_A, PARENT_B, &indeces);
} // end Constructor 3


Gene::Gene(const Gene& other)
{
	ui_length = other.length();
	bounds = other.bounds;

	std::copy(other.gene.begin(), other.gene.end(), gene.begin());
} // end Copy Constructor


void Gene::mutate(const Mutation_Info MUT_INFO)
{
	// getRandomNumberInRage returns a number in range [a,b), thus we need to add a little bit to b to make the range [a,b]
	double d = getRandomRealInRange<double>(0.0, (1.0 + std::numeric_limits<double>::min()));

	if (d - MUT_INFO.d_rate <= 0)
	{
		size_t i = getRandomIntInRange<size_t>(0, ui_length);

		double new_value = getRandomRealInRange(bounds.d_min, bounds.d_max);

		(*this)[i] = new_value;
	} // end if
} // end method mutate


inline size_t Gene::length(void) const
{
	return ui_length;
} // end method length


inline double Gene::fitness(void) const
{
	return d_fitness;
} // end methog fitness


inline void Gene::evaluate(fitnessFunction f)
{
	d_fitness = f(&gene);
} // end method evaluate


double& Gene::operator[](const size_t i)
{
	if (i >= ui_length)
	{
		throw out_of_range("index out of bounds.");
	} // end if

	return gene.at(i);
} // end operator[]


double Gene::operator[](const size_t i) const
{
	if (i >= ui_length)
	{
		throw out_of_range("index out of bounds.");
	} // end if

	return gene.at(i);
} // end operator[]


inline bool Gene::operator<(const Gene & other) const
{
	return d_fitness < other.d_fitness;
} // end operator>

 
void Gene::recombine(const Gene & PARENT_A, const Gene & PARENT_B, const std::vector<size_t>* indeces)
{
	// this binary string is the template for the new gene
	// 0 means take from parent a, 1 means take from parent b
	vector<size_t>* distribution = getRandomBinaryString<size_t>(indeces->size());

	// indeces we are compying
	size_t	start = 0,
			end = indeces->at(0);

	// iterate over all cross-over points
	for (size_t j = 1; j < indeces->size(); j++)
	{
		// pointer to current parent to avoid redundant code
		const Gene* temp = (distribution->at(j) == 0) ? (&PARENT_A) : (&PARENT_B);

		// do the cross over for all parts in the current region
		for (size_t k = start; k < end; k++)
		{
			gene.push_back(temp->gene.at(k));
		} // end for

		start = end;
		end = indeces->at(j);
	} // end for
} // end method recombine


std::ostream& operator<<(std::ostream& stream, const Gene& gene)
{
	if (gene.length() > 0)
	{
		stream << gene[0];

		for (size_t i = 1; i < gene.length(); i++)
		{
			stream << ", " << gene[i];
		} // end for

		stream << endl;
	} // end if

	return stream;
} // end operator<<



