#include "results.hpp"
#include <limits>    // numeric_limits

using namespace std;

results_t::results_t(void)
{
	d_bestValue = std::numeric_limits<double>::max();
	d_finalDeltaX = d_avgTime = 0;
	ui_functionCalls = 0;
} // end Constructor


results_t::~results_t(void)
{
	bestValues.clear();
} // end Destructor


void results_t::operator=(const Gene* gene)
{
	d_bestValue = gene->d_fitness;
	bestValues = gene->gene;
} // end operator=


std::ostream& operator<<(ostream& stream, results_t& res)
{
	if (res.bestValues.size() > 0)
	{
		stream << "Dimensions: " << res.bestValues.size() << "\n";
	} // end if

	stream << "Optimal solution found: " << res.d_bestValue << "\n";

	stream << "Time to compute: " << res.d_avgTime << "\n";

	stream << "Function calls made: " << res.ui_functionCalls << "\n";

	stream << "Final delta x value: " << res.d_finalDeltaX << "\n";

	if (res.bestValues.size() > 0)
	{
		stream << "Optimal point: [ ";

		for (size_t i = 0; i < res.bestValues.size(); i++)
		{
			stream << res.bestValues.at(i);

			if ((i + 1) < res.bestValues.size())
			{
				stream << ", ";
			} // end if
		} // end for

		stream << " ]" << endl;
	} // end if

	return stream;
} // end operator << 