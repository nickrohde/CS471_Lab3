#include <fstream>
#include <sstream>
#include "Test.hpp"
#include <omp.h>
#include "GA.hpp"
#include "DE_Strategies.hpp"


#define X_OVER_POINTS 4
#define X_OVER_RATE 0.75

#define MUT_RATE 0.15
#define MUT_RANGE 25.0
#define MUT_PREC 0.89

#define POP_SIZE 100
#define NUM_GEN 100
#define ER 0.2

#define NUM_THREADS 16

using namespace std;

/*
void Test::runTest(void)
{
	Mutation_Info MUT_INFO(MUT_RATE, MUT_RANGE, MUT_PREC);
	Crossing_Over_Info CR_INFO(X_OVER_POINTS, X_OVER_RATE);

	size_t max_dim = 30;

	timePoint end = highRes_Clock::now();
	timePoint start = highRes_Clock::now();

	results_t* res;
	Population_Info POP_INFO;
	double avg_time = 0.0;

	for (size_t i = 0; i < 15; i++)
	{
		if (i == 14)
		{
			max_dim = 10;
		}

	#pragma omp parallel for private(res, POP_INFO) reduction(+ : avg_time) num_threads(NUM_THREADS)
		for (int j = 10; j <= max_dim; j += 10)
		{
			POP_INFO = Population_Info(100, j, 100, 0.2);

			ofstream file(makeFileName(j,i), ios::app | ios::out);

			avg_time = 0.0;

			for (size_t k = 0; k < 100; k++)
			{
				res = geneticAlgorithm(fitnessFunctions[i], POP_INFO, da_ranges[i], MUT_INFO, CR_INFO);
			
				file << res->d_bestValue;

				if (k < 99)
				{
					file << ",";
				}

				delete res;
			}
			#pragma omp critical
			{
				cout << "Average time for f_" << (i + 1) << " in " << j << " dimensions: " << (avg_time / 100.0) << endl;
			}
			file.close();
		}
	}

	end = highRes_Clock::now();

	duration compute_time = std::chrono::duration_cast<duration>(end - start);
	cout << "Overall time of test: " << compute_time.count() << endl;
}
/*/

void Test::runTest(void)
{
	Mutation_Info MUT_INFO(MUT_RATE, MUT_RANGE, MUT_PREC);
	Crossing_Over_Info CR_INFO(X_OVER_POINTS, X_OVER_RATE);

	size_t max_dim = 30;

	timePoint end = highRes_Clock::now();
	timePoint start = highRes_Clock::now();

	results_t* res;
	Population_Info POP_INFO;
	double* avg_time = new double[3];


	size_t* numbers;

	double** data = new double*[3];
	data[0] = new double[100];
	data[1] = new double[100];
	data[2] = new double[100];


	for (size_t i = 0; i < 15; i++)
	{
		if (i == 14)
		{
			max_dim = 10;
		}

		avg_time[0] = 0.0;
		avg_time[1] = 0.0;
		avg_time[2] = 0.0;

		int j = 10;
		#pragma omp parallel for private(numbers, res, POP_INFO, j) num_threads(NUM_THREADS)
		for (j = 10; j <= max_dim; j += 10)
		{
			POP_INFO = Population_Info(POP_SIZE, j, NUM_GEN, ER);

			numbers = new size_t[POP_SIZE];

			for (size_t z = 0; z < POP_SIZE; z++)
			{
				numbers[z] = z;
			}

			for (size_t k = 0; k < 100; k++)
			{
				res = DifferentialEvolution::differentialEvolution(fitnessFunctions[i], POP_INFO, da_ranges[i], CR_INFO, DE_Strategy::DE_BEST_1_EXP, numbers);

				data[(j/10)-1][i] = res->d_bestValue;

				#pragma omp critical
				{
					avg_time[(j/10)-1] += res->d_avgTime;
				}

				delete res;
			}

			delete[] numbers;
		} // end for j

		for(size_t k = 0; k < 3; k++)
		{
			ofstream file2("times.txt", ios::app | ios::out);

			file2 << (avg_time[k] / 100);

			if (k < 2)
			{
				file2 << ", ";
			}
			else
			{
				file2 << "\n";
			}

			file2.close();

			ofstream file(makeFileName(10*(k+1), i), ios::app | ios::out);

			for (size_t j = 0; j < 100; j++)
			{
				file << data[k][i];

				if (j < 99)
				{
					file << ",";
				}
			}
			file.close();
		}
	}

	delete[] data[0];
	delete[] data[1];
	delete[] data[2];
	delete[] data;

	end = highRes_Clock::now();


	duration compute_time = std::chrono::duration_cast<duration>(end - start);
	std::cout << "Overall time of test: " << compute_time.count() << endl;
}

//*/

Test::Test(void)
{
	da_ranges = new Bounds[NUMBER_FUNCTIONS]; // array containing the bounds of each function
	da_A = new double*[SHEKEL_OUTER_SIZE]; // shekels foxhole parameter that is bound to the function

	// these two function only exist to make the constructor shorter
	makeRanges(da_ranges); // make array with ranges for functions
	makeMatrix(da_A); // make matrix A for shekels foxhole

	ui_minDimensions = 10;
	ui_maxDimensions = 30;
	ui_dimensionDelta = 10;
	b_storeData = true;

	fitnessFunctions = getAllCostFunctions(const_cast<const double**>(da_A), ui_SHEKEL_M); // vector containing the cost functions

	compute_start = compute_end = highRes_Clock::now();
} // end Default Constructor


Test::Test(vector<double>* lsd, size_t ui_dimMin, size_t ui_dimMax, size_t ui_dimDelta, bool b_storeRes)
{
	ui_minDimensions = ui_dimMin;
	ui_maxDimensions = ui_dimMax;
	ui_dimensionDelta = ui_dimDelta;
	b_storeData = b_storeRes;

	compute_start = compute_end = highRes_Clock::now();

	da_ranges = new Bounds[NUMBER_FUNCTIONS]; // array containing the ranges for the RNG; [i][0] contains min, [i][1] contains max for function f_i
	da_A = new double*[SHEKEL_OUTER_SIZE]; // shekels foxhole parameter that is bound to the function

	// these two function only exist to make the constructor shorter
	makeRanges(da_ranges); // make matrix with ranges for functions
	makeMatrix(da_A); // make matrix A for shekels foxhole

	fitnessFunctions = getAllCostFunctions(const_cast<const double**>(da_A), ui_SHEKEL_M); // vector containing the cost functions
} // end Constructor 4


Test::~Test(void)
{
	try
	{
		if (da_A != nullptr)
		{
			for (int i = 0; i < SHEKEL_OUTER_SIZE; i++)
			{
				delete[] da_A[i];
			} // end for

			delete[] da_A;
		} // end if	
	}
	catch (exception e)
	{
		cout << "deleting matrix broke" << endl;
	}
	try
	{
		if (da_ranges != nullptr)
		{
			delete[] da_ranges;
		} // end if
	}
	catch (exception e)
	{
		cout << "deleting matrix broke" << endl;
	}	
} // end Destructor


inline void Test::makeMatrix(double**& da_A)
{
	da_A[0]  = new double[SHEKEL_INNER_SIZE]{ 9.681, 0.667, 4.783, 9.095, 3.517, 9.325, 6.544, 0.211, 5.122, 2.02 };
	da_A[1]  = new double[SHEKEL_INNER_SIZE]{ 9.4, 2.041, 3.788, 7.931, 2.882, 2.672, 3.568, 1.284, 7.033, 7.374 };
	da_A[2]  = new double[SHEKEL_INNER_SIZE]{ 8.025, 9.152, 5.114, 7.621, 4.564, 4.711, 2.996, 6.126, 0.734, 4.982 };
	da_A[3]  = new double[SHEKEL_INNER_SIZE]{ 2.196, 0.415, 5.649, 6.979, 9.510, 9.166, 6.304, 6.054, 9.377, 1.426 };
	da_A[4]  = new double[SHEKEL_INNER_SIZE]{ 8.074, 8.777, 3.467, 1.863, 6.708, 6.349, 4.534, 0.276, 7.633, 1.567 };
	da_A[5]  = new double[SHEKEL_INNER_SIZE]{ 7.650, 5.658, 0.720, 2.764, 3.278, 5.283, 7.474, 6.274, 1.409, 8.208 };
	da_A[6]  = new double[SHEKEL_INNER_SIZE]{ 1.256, 3.605, 8.623, 6.905, 4.584, 8.133, 6.071, 6.888, 4.187, 5.448 };
	da_A[7]  = new double[SHEKEL_INNER_SIZE]{ 8.314, 2.261, 4.24, 1.781, 4.124, 0.932, 8.129, 8.658, 1.208, 5.762 };
	da_A[8]  = new double[SHEKEL_INNER_SIZE]{ 0.226, 8.858, 1.42, 0.954, 1.622, 4.698, 6.228, 9.096, 0.972, 7.637 };
	da_A[9]  = new double[SHEKEL_INNER_SIZE]{ 7.305, 2.228, 1.242, 5.928, 9.133, 1.826, 4.06, 5.204, 8.713, 8.247 };
	da_A[10] = new double[SHEKEL_INNER_SIZE]{ 0.652, 7.027, 0.508, 4.876, 8.807, 4.632, 5.808, 6.937, 3.291, 7.016 };
	da_A[11] = new double[SHEKEL_INNER_SIZE]{ 2.699, 3.516, 5.847, 4.119, 4.461, 7.496, 8.817, 0.69, 6.593, 9.789 };
	da_A[12] = new double[SHEKEL_INNER_SIZE]{ 8.327, 3.897, 2.017, 9.57, 9.825, 1.15, 1.395, 3.885, 6.354, 0.109 };
	da_A[13] = new double[SHEKEL_INNER_SIZE]{ 2.132, 7.006, 7.136, 2.641, 1.882, 5.943, 7.273, 7.691, 2.88, 0.564 };
	da_A[14] = new double[SHEKEL_INNER_SIZE]{ 4.707, 5.579, 4.08, 0.581, 9.698, 8.542, 8.077, 8.515, 9.231, 4.67 };
	da_A[15] = new double[SHEKEL_INNER_SIZE]{ 8.304, 7.559, 8.567, 0.322, 7.128, 8.392, 1.472, 8.524, 2.277, 7.826 };
	da_A[16] = new double[SHEKEL_INNER_SIZE]{ 8.632, 4.409, 4.832, 5.768, 7.05, 6.715, 1.711, 4.323, 4.405, 4.591 };
	da_A[17] = new double[SHEKEL_INNER_SIZE]{ 4.887, 9.112, 0.17, 8.967, 9.693, 9.867, 7.508, 7.77, 8.382, 6.74 };
	da_A[18] = new double[SHEKEL_INNER_SIZE]{ 2.44, 6.686, 4.299, 1.007, 7.008, 1.427, 9.398, 8.48, 9.95, 1.675 };
	da_A[19] = new double[SHEKEL_INNER_SIZE]{ 6.306, 8.583, 6.084, 1.138, 4.350, 3.134, 7.853, 6.061, 7.457, 2.258 };
	da_A[20] = new double[SHEKEL_INNER_SIZE]{ 0.652, 2.343, 1.37, 0.821, 1.31, 1.063, 0.689, 8.819, 8.833, 9.07 };
	da_A[21] = new double[SHEKEL_INNER_SIZE]{ 5.558, 1.272, 5.756, 9.857, 2.279, 2.764, 1.284, 1.677, 1.244, 1.234 };
	da_A[22] = new double[SHEKEL_INNER_SIZE]{ 3.352, 7.549, 9.817, 9.437, 8.687, 4.167, 2.57, 6.54, 0.228, 0.027 };
	da_A[23] = new double[SHEKEL_INNER_SIZE]{ 8.798, 0.88, 2.37, 0.168, 1.701, 3.68, 1.231, 2.39, 2.499, 0.064 };
	da_A[24] = new double[SHEKEL_INNER_SIZE]{ 1.46, 8.057, 1.337, 7.217, 7.914, 3.615, 9.981, 9.198, 5.292, 1.224 };
	da_A[25] = new double[SHEKEL_INNER_SIZE]{ 0.432, 8.645, 8.774, 0.249, 8.081, 7.461, 4.416, 0.652, 4.002, 4.644 };
	da_A[26] = new double[SHEKEL_INNER_SIZE]{ 0.679, 2.8, 5.523, 3.049, 2.968, 7.225, 6.73, 4.199, 9.614, 9.229 };
	da_A[27] = new double[SHEKEL_INNER_SIZE]{ 4.263, 1.074, 7.286, 5.599, 8.291, 5.2, 9.214, 8.272, 4.398, 4.506 };
	da_A[28] = new double[SHEKEL_INNER_SIZE]{ 9.496, 4.83, 3.15, 8.27, 5.079, 1.231, 5.731, 9.494, 1.883, 9.732 };
	da_A[29] = new double[SHEKEL_INNER_SIZE]{ 4.138, 2.562, 2.532, 9.661, 5.611, 5.5, 6.886, 2.341, 9.699, 6.5 };
} // end method makeMatrix


inline void Test::makeRanges(Bounds*& da_ranges)
{
	da_ranges[0]  = Bounds(-512.0, 512.0);
	da_ranges[1]  = Bounds(-100.0, 100.0);
	da_ranges[2]  = Bounds(-100.0, 100.0);
	da_ranges[3]  = Bounds(-30.0,   30.0);
	da_ranges[4]  = Bounds(-500.0, 500.0);
	da_ranges[5]  = Bounds(-30.0,   30.0);
	da_ranges[6]  = Bounds(-30.0,   30.0);
	da_ranges[7]  = Bounds(-32.0,   32.0);
	da_ranges[8]  = Bounds(-32.0,   32.0);
	da_ranges[9]  = Bounds(-500.0, 500.0);
	da_ranges[10] = Bounds(-500.0, 500.0);
	da_ranges[11] = Bounds(-100.0, 100.0);
	da_ranges[12] = Bounds(   0.0,  _PI );
	da_ranges[13] = Bounds(- 30.0,  30.0);
	da_ranges[14] = Bounds(   0.0,  10.0);
} // end method makeRanges


void Test::dumpDataToFile(string s_name, results_t* res)
{
	ofstream file(s_name, ios::out | ios::app);

	if (!file.bad() && file.is_open())
	{
		file << res->d_bestValue << "\n";
	} // end if

	file.close();
} // end dumpDataToFile


void Test::writeResultsToFile(results_t* res)
{
	ofstream file("results.csv", ios::out | ios::app);

	if (!file.bad() && file.is_open())
	{
		file << *res;
	} // end if

	file.close();
} // end method 


string Test::makeFileName(size_t ui_dim, int i_functionNumber)
{
	stringstream name;

	name << "DE1_" << ui_dim << "_f" << (i_functionNumber + 1) << ".csv" ;

	return name.str();
}


