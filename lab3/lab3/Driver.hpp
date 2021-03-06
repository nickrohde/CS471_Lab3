#pragma once

#ifndef _DRIVER_H
#define _DRIVER_H

#include "MasterInclude.hpp"

typedef std::chrono::high_resolution_clock::time_point timePoint;
typedef std::chrono::duration<double> duration;
typedef std::chrono::high_resolution_clock highRes_Clock;

/// <summary>Converts a string to type T.</summary>
/// <typeparam name="T">A type that can be extracted from a string using stringstream.</typeparam>
/// <param name="s">The string to convert.</param>
/// <returns>An equivalent T object to the string, if such an object exists, otherwise a default object of type T.</returns>
template <typename T>
inline T convertStringToType(const std::string s)
{
	T t;
	std::stringstream ss;

	ss << s;
	ss >> t;

	return t;
} // end template convertStringToType

/// <summary>Class that runs the program.</summary>
class Driver
{
public:

	/// <summary>Default constructor.</summary>
	Driver(void);

	/// <summary>Constructor taking the name of a .ini file.</summary>
	/// <param name="s_fileName">Name of the .ini file to parse for configuration settings.</param>
	Driver(std::string s_fileName);

	/// <summary>Destructor.</summary>
	/// <remarks>Objects of this type own no memory, so this does nothing. The test pointer is owned by the function run, and it destroys it upon exiting.</remarks>
	~Driver(void) {}

	/// <summary>Prompts the user to chose a optimization strategy, and then runs the tests using that strategy.</summary>
	/// <returns>0 on successful execution, 1 otherwise.</returns>
	int run(void);

	/// <summary>Prompts the user to answer yes or no to some question.</summary>
	/// <returns>The user's choice.</returns>
	static char askUserYesNo(void);

	/// <summary>Clears the input buffer.</summary>
	static void clearInput(void);

	/// <summary>Returns whether or not the object is in a valid state.</summary>
	/// <returns>True iff the object is valid, false otherwise.</returns>
	bool isValid(void);

private:
	/// <summary>Parameters extracted from the .ini file.</summary>
	size_t	ui_iterations,
			ui_generations,
			ui_startDim,
			ui_endDim,
			ui_dimDelta,
			ui_GA_CP,
			ui_strat;

	/// <summary>Parameter extracted from the .ini file.</summary>
	bool	b_storeData,
	/// <summary>Whether or not the object is in an invalid state.</summary>
			b_invalid,
	/// <summary>Tells run that the user wants to quit after trying to enter a file name.</summary>
			b_stop;	

	/// <summary>Parameters extracted from the .ini file.</summary>
	double  d_ER,
			d_DE_CR,
			d_DE_MR,
			d_GA_CR,
			d_GA_MR,
			d_GA_MRg,
			d_GA_MP;

	/// <summary>Timing of each run.</summary>
	timePoint	compute_start,
				compute_end;
	duration	time_to_compute;

	/// <summary>Displays the main menu to the user.</summary>
	void presentMenu(void);

	/// <summary>Gets the user's choice from stdio.</summary>
	/// <returns>The user's choice (always valid).</returns>
	char getChoice(void);

	/// <summary>Prompts the user to enter a file name for a .ini file.</summary>
	/// <returns>Name of a file (this file exists and is not empty).</returns>
	std::string askUserForFileName(void);

	/// <summary>Initializes this object by parsing the .ini file, upon success it sets b_invalid to false.</summary>
	/// <exception cref="std::invalid_argument">Thrown if the .ini file is (1) missing an expected key, or (2) a key value is invalid.</exception>  
	void initialize(const std::string s_fileName);
}; // end class Driver


#endif // !_DRIVER_H
