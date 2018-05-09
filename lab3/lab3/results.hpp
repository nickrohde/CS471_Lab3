#pragma once

#ifndef _RESULTS_H
#define _RESULTS_H

#include "MasterInclude.hpp"
#include "Gene.hpp"  // Gene

/// <summary>Storage class for results.</summary>
struct results_t
{
	// Functions:
	// Constructor:
	/// <summary>Default Constructor.</summary>
	results_t(void);

	// Destructor:
	/// <summary>Destructor.</summary>
	~results_t(void);

	// Operators:
	/// <summary>Stream insertion operator. Inserts the contents of this object into the output stream object <paramref name="stream"/>.</summary>
	/// <param name="stream">The stream into which this object's string representation will be inserted.</param>
	/// <param name="res">A results_t object containing some data; this object can be invalid.</param>
	/// <returns>The stream passed in <paramref name="stream"/> with this object's contents in it.</returns>
	friend std::ostream& operator<<(std::ostream& stream, results_t& res);

	void operator=(const Gene* gene);

	// Data Members:
	/// <summary>Average time of function execution.</summary>
	double	d_avgTime,

	/// <summary>Best value found during test.</summary>
			d_bestValue,
	/// <summary>The final value of the delta x parameter. This is only used by ILS</summary>
			d_finalDeltaX;

	/// <summary>Stores # of function calls made.</summary>
	std::size_t ui_functionCalls;

	/// <summary>Best input vector found.</summary>
	std::vector<double> bestValues;
}; // end Struct results_t

#endif