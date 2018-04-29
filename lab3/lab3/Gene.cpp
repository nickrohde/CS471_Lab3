#include "Gene.hpp"

using namespace std;

Gene::Gene(const size_t ui_SIZE, const double  d_MIN, const double  d_MAX)
{
	ui_length = ui_SIZE;
	d_min = d_MIN;
	d_max = d_MAX;

	for (size_t i = 0; i < ui_length; i++)
	{
		gene.push_back(getRandomNumberInRange(d_MIN, d_MAX));
	} // end for
} // end Constructor 3


Gene::~Gene(void){}


void Gene::mutate(const double d_MR)
{
	double d = getRandomNumberInRange<double>(0.0, 1.0);

	if (d - d_MR <= 0)
	{
		size_t i = getRandomNumberInRange<size_t>(0, ui_length - 1);

		double new_value = getRandomNumberInRange(d_min, d_max);

		(*this)[i] = new_value;
	} // end if
} // end method mutate


inline size_t Gene::length(void) const
{
	return ui_length;
} // end method length


double& Gene::operator[](size_t i)
{
	return gene.at(i);
} // end operator[]


double Gene::operator[](size_t i) const
{
	return gene.at(i);
} // end operator[]


std::ostream& operator<<(std::ostream& stream, const Gene& gene)
{
	if (gene.length > 0)
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
