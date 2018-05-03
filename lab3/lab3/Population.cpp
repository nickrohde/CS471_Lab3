#include "Population.hpp"

using namespace std;

Population::Population(void)
{
	ui_size = 0;
} // end Default Constructor


Population::Population(const size_t ui_SIZE, const size_t ui_DIM, const Bounds bounds)
{
	ui_size = ui_SIZE;

	for (size_t i = 0; i < ui_size; i++)
	{
		genes.push_back(Gene(ui_DIM, bounds));
	} // end for
} // end Constructor 4


Population::Population(const Population & other)
{
	ui_size = other.ui_size;

	std::copy(other.genes.begin(), other.genes.end(), genes.begin());
} // end Copy Constructor


inline size_t Population::size(void) const
{
	return ui_size;
} // end method size


inline Gene& Population::operator[](const size_t i)
{
	if (i >= ui_size)
	{
		throw out_of_range("index out of bounds.");
	} // end if

	return genes.at(i);
} // end operator[]


inline Gene Population::operator[](const size_t i) const
{
	if (i >= ui_size)
	{
		throw out_of_range("index out of bounds.");
	} // end if

	return genes.at(i);
} // end operator[]


inline void Population::sort(void)
{
	std::sort(genes.begin(), genes.end(), std::less<Gene>());
} // end method sort


ostream& operator<<(ostream& stream, const Population& pop)
{
	stream << endl;

	for (auto& g : pop.genes)
	{
		stream << g << endl;
	} // end for

	return stream;
} // end operator<<

