#pragma once

// Includes:
#include <iostream>
#include <limits>
#include <Windows.h>


// Defines:
#define DEFAULT          0
#define DEFAULT_CAPACITY 5


// Matrix class definition
class Matrix
{
public:
	/// <summary>Creates an empty matrix of size 0 times 0.</summary>
	Matrix(void);

	/// <summary>Creates an identity matrix of size <paramref name="ui_SIZE"/> x <paramref name="ui_SIZE"/>.</summary>
	/// <param name="ui_SIZE">The size of this square matrix.</param>
	Matrix(const size_t ui_SIZE);

	/// <summary>Creates a matrix of size <paramref name="ui_HEIGHT"/> times <paramref name="ui_WIDTH"/> filled with 0s.</summary>
	/// <param name="ui_HEIGHT">Height of this matrix.</param>
	/// <param name="ui_WIDTH">Width of this matrix.</param>
	Matrix(const size_t ui_HEIGHT, size_t ui_WIDTH);

	/// <summary>Creates a copy of the matrix <paramref name="m_OTHER"/>.</summary>
	/// <param name="m_OTHER">Matrix to be copied.</param>
	/// <remarks>This is an inefficient copy mechanism, if the matrix <paramref name="m_OTHER"/> is no longer needed, use move constructor.</remarks>
	Matrix(const Matrix&);

	/// <summary>Creates a copy of the matrix <paramref name="m_OTHER"/>.</summary>
	/// <param name="m_other">The matrix to be copied. This object will be destroyed during the process.</param>
	/// <remarks>This constructor will destroy the matrix <paramref name="m_OTHER"/>. Runtime is guaranteed to be O(1).</remarks>
	Matrix(Matrix&&);


	/// <summary>Destructor, releases all dynamic memory owned by this object.</summary>
	~Matrix(void);


	/// <summary>Getter for the height of the visible matrix.</summary>
	/// <returns>The height of the visible matrix.</returns>
	size_t getHeight(void) const;

	/// <summary>Getter for the width of the visible matrix.</summary>
	/// <returns>The width of the visible matrix.</returns>
	size_t getWidth(void) const;
    

	/// <summary>Resizes the visible matrix to the size <paramref name="ui_h"/> x <paramref name="ui_w"/> if there is enough memory.</summary>
	/// <param name="ui_h">The new height.</param>
	/// <param name="ui_w">The new width.</param>
	/// <remarks>The matrix is only resized if needed, the capacity of the matrix determines whether or not this will occur. 
	/// Shrinking the matrix will always take O(1), increasing it will take, on average, O(2n).</remarks>
	void resize(size_t ui_h, size_t ui_w);

	/// <summary>Transposes this matrix.</summary>
	/// <remarks>This function only changes the way the matrix is interpreted, runtime is always O(1).</remarks>
	void transpose(void);


	/// <summary>Copies the contents of <paramref name="m_OTHER"/> into this matrix. The matrix will be resized as needed.</summary>
	/// <param name="m_OTHER">The matrix to be copied.</param>
	/// <returns>This.</returns>
	/// <remarks>This is an inefficient copy mechanism, if the matrix <paramref name="m_OTHER"/> is no longer needed, use move assignment.</remarks>
	Matrix& operator= (const Matrix&);

	/// <summary>Moves the contents of <paramref name="m_other"/> into this matrix.</summary>
	/// <param name="m_other">The matrix to be copied. This object will be destroyed during the process.</param>
	/// <returns>This.</returns>
	/// <remarks>This operator will destroy the matrix <paramref name="m_other"/>. Runtime is guaranteed to be O(1).</remarks>
	Matrix& operator= (Matrix&&);


	/// <summary>Accessor to the values stored inside the matrix.</summary>
	/// <param name="ui_ROW">The row index of the value.</param>
	/// <param name="ui_COL">The column index of the value.</param>
	/// <returns>The value at (<paramref name="ui_ROW"/>, <paramref name="ui_COL"/>), if such a value exists.</returns>
	double& operator()(const size_t ui_ROW, const size_t ui_COL);

	/// <summary>Accessor to the values stored inside the matrix.</summary>
	/// <param name="ui_ROW">The row index of the value.</param>
	/// <param name="ui_COL">The column index of the value.</param>
	/// <returns>The value at (<paramref name="ui_ROW"/>, <paramref name="ui_COL"/>), if such a value exists.</returns>
	double operator()(const size_t ui_ROW, const size_t ui_COL) const;


	/// <summary>Creates a new matrix containing the sum of this matrix and the matrix <paramref name="m_OTHER"/>.</summary>
	/// <param name="m_OTHER">The RHS operand of the addition.</param>
	/// <returns>A new matrix containing the sum of this and <paramref name="m_OTHER"/>.</returns>
	Matrix operator+(const Matrix& m_OTHER) const;

	/// <summary>Adds the matrix <paramref name="m_OTHER"/> to this matrix.</summary>
	/// <param name="m_OTHER">The matrix to be added to this matrix.</param>
	/// <returns>This.</returns>
	Matrix& operator+=(const Matrix& m_OTHER);


	/// <summary>Creates a new matrix that is the product of <paramref name="m_OTHER"/> and this.</summary>
	/// <param name="m_OTHER">The RHS operand of the multiplication.</param>
	/// <returns>A new matrix containing the matrix product of this and <paramref name="m_OTHER"/>.</returns>
	Matrix operator*(const Matrix& m_OTHER) const;

	/// <summary>Multiplies the matrix <paramref name="m_OTHER"/> by this matrix.</summary>
	/// <param name="m_OTHER">The matrix that this should be multiplied by.</param>
	/// <returns>This.</returns>
	Matrix& operator*=(const Matrix& m_OTHER);


	/// <summary>Creates a new matrix that is the product of <paramref name="d_VAL"/> and this.</summary>
	/// <param name="d_VAL">The scalar factor to multiply by.</param>
	/// <returns>A matrix containing the scalar product of this and <paramref name="d_VAL"/>.</returns>
	Matrix operator*(const double d_VAL) const;

	/// <summary>Multiplies this matrix by the scalar factor <paramref name="d_VAL"/>.</summary>
	/// <param name="d_VAL">The scalar factor to multiply by.</param>
	/// <returns>This.</returns>
	Matrix& operator*=(const double d_VAL);


	/// <summary>Checks if the given matrices are equivalent. This only compares the visible portions of the matrix.</summary>
	/// <param name="m_OTHER">The other matrix to compare this with.</param>
	/// <returns>True iff the two matrices have the same height, width, and equivalent contents in all visible fields.</returns>
	bool operator==(const Matrix& m_OTHER) const;

private:
	// Private data members:
	/// <summary>The number of visible inner arrays.</summary>
    size_t	 ui_height    , 
	/// <summary>The visible size of the inner arrays.</summary>
		     ui_width     , 
	/// <summary>The actual number of inner arrays.</summary>
		     ui_capacityH ,
	/// <summary>The actual size of the inner arrays.</summary>
			 ui_capacityW ;

	/// <summary>Controls whether this matrix is transposed or not.</summary>
	/// <remarks>T: matrix is transposed, height is interpreted as width, and vice versa; 
	///			 F: matrix is not tranposed	</remarks>
	bool     b_transposed; 

	/// <summary>The array containing the matrix values.</summary>
    double** dp_data     ;


	// Private Methods:
	// Operations:
	/// <summary>Initializes the array containing the matrix, the array will have dimensions <paramref name="ui_SIZE"/> x <paramref name="ui_SIZE"/>.</summary>
	/// <param name="dp_arr">The array to initialize.</param>
	/// <param name="ui_SIZE">The size to initialize this with.</param>
	void instantiate(double ** dp_arr, const size_t ui_SIZE);

	/// <summary>Initializes the array containing the matrix, the array will have dimensions <paramref name="ui_HEIGHT"/> x <paramref name="ui_WIDTH"/> and nulls all indices.</summary>
	/// <param name="dp_arr">The array to initialize.</param>
	/// <param name="ui_HEIGHT">The height to initialize this with.</param>
	/// <param name="ui_WIDTH">The width to initialize this with.</param>
	void instantiate(double ** dp_arr, const size_t ui_HEIGHT, const size_t ui_WIDTH);

	/// <summary>Copies contents of the matrix <paramref name="m_OTHER"/> into this matrix.</summary>
	/// <param name="m_OTHER">The matrix to be copied into this.</param>
	/// <param name="ui_HEIGHT">The height of the new matrix.</param>
	/// <param name="ui_WIDTH">The width of the new matrix.</param>
	void copy(const Matrix & m_OTHER, const size_t ui_HEIGHT, const size_t ui_WIDTH);

	/// <summary>Helper method for resize, determines whether or not a resize is required.</summary>
	/// <param name="ui_HEIGHT">The new height of this matrix.</param>
	/// <param name="ui_WIDTH">The new width of this matrix.</param>
	void resizeHelper(const size_t ui_HEIGHT, const size_t ui_WIDTH);

	/// <summary>Performs the resize operation when required.</summary>
	/// <param name="ui_HEIGHT">The new height of this matrix.</param>
	/// <param name="ui_WIDTH">The new width of this matrix.</param>=
	void resizeMatrix(const size_t ui_HEIGHT, const size_t ui_WIDTH);

	/// <summary>Zeros out invisible portions of the matrix after a resize.</summary>
	/// <param name="ui_HEIGHT">The new height of this matrix.</param>
	/// <param name="ui_WIDTH">The new width of this matrix.</param>
	void removeOld(const size_t ui_HEIGHT, const size_t ui_WIDTH);

	/// <summary>Deallocates all dynamic memory belonging to this object.</summary>
	void deleteContents(void);

	/// <summary>Prints the matrix to stdout -- includes invisible portions.</summary>
	void printMatrix(void);


	// Setters:
	/// <summary>Private setter for the height.</summary>
	/// <param name="ui_HEIGHT">New height of the matrix.</param>
	inline void setHeight(const size_t ui_HEIGHT);

	/// <summary>Private setter for the width.</summary>
	/// <param name="ui_WIDTH">New width of the matrix.</param>
	inline void setWidth(const size_t ui_WIDTH);

	/// <summary>Private setter for the capacity of this matrix.</summary>
	/// <param name="ui_CAPACITY_H">The new height capacity of this matrix.</param>
	/// <param name="ui_CAPACITY_W">The new width capacity of this matrix.</param>
	inline void setCapacity(const size_t ui_CAPACITY_H, const size_t ui_CAPACITY_W);


	// Getters:
	/// <summary>Private getter for the height capacity of this matrix.</summary>
	/// <returns>The height capacity of this matrix.</returns>
	inline size_t getCapacityH(void);
	
	/// <summary>Private getter for the width capacity of this matrix.</summary>
	/// <returns>The width capacity of this matrix.</returns>
	inline size_t getCapacityW(void);
}; // end Class Matrix
