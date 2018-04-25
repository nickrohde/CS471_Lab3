
// Includes:
#include "matrix.hpp"


// Namespace:
using namespace std;


// Constructors:
Matrix::Matrix(void)
{
	setHeight(DEFAULT);
	setWidth (DEFAULT);
	setCapacity(DEFAULT_CAPACITY, DEFAULT_CAPACITY);
	b_transposed = false;

	this->dp_data = new double*[getCapacityH()];
	instantiate(this->dp_data, getCapacityH());
} // end default Constructor 


Matrix::Matrix(const size_t ui_SIZE)
{
	// Variables:
	size_t ui_size = max(DEFAULT, ui_SIZE); // input check

    // accessible region of matrix
	setHeight(ui_size); 
	setWidth (ui_size); 

	// to avoid running out of memory with large matrices
	if (ui_size < 5500)
	{
		setCapacity(ui_size * 2, ui_size * 2); // actual dimensions of matrix
	} // end if
	else
	{
		setCapacity(ui_size, ui_size);
	} // end else
	
	b_transposed = false; // matrix is currently in normal state

	this->dp_data = new double*[getCapacityH()]; // create values array

	instantiate(this->dp_data, getCapacityH()); // instantiate inner arrays and fill with 0

	// fill diagonal with 1s 
	for (size_t i = DEFAULT; i < ui_size; i++)
	{
		dp_data[i][i] = 1;
	} // end for
} // end Constructor


Matrix::Matrix(const size_t ui_HEIGHT, const size_t ui_WIDTH)
{
	// Variables: 
	size_t ui_h = max(DEFAULT, ui_HEIGHT); // input check
	size_t ui_w = max(DEFAULT, ui_WIDTH);  // input check


	setHeight(ui_h); // accessible region of array
	setWidth(ui_w);  // accessible region of array

	// to avoid running out of memory with large matrices
	if (ui_h < 5500 && ui_w < 5500)
	{
		setCapacity(ui_h * 2, ui_w * 2); // actual dimensions of matrix
	} // end if
	else
	{
		setCapacity(ui_h, ui_w);
	} // end else

	b_transposed = false; // matrix is currently in normal state

	this->dp_data = new double*[getCapacityH()]; // create values array
	instantiate(dp_data, getCapacityH(), getCapacityW()); // instatiate inner arrays and fill with 0s
} // end Constructor 


Matrix::Matrix(const Matrix & m_OTHER)
{
	// copy over members
	setHeight(m_OTHER.getHeight());
	setWidth(m_OTHER.getWidth());
	setCapacity(m_OTHER.ui_capacityH, m_OTHER.ui_capacityW);

	b_transposed = false; // new matrix will not be transposed, regardless of whether the other one is

	dp_data = new double*[getCapacityH()]; // create values array

	instantiate(this->dp_data, getCapacityH(), getCapacityW()); // instatiate inner arrays and fill with 0s

	copy(m_OTHER, getHeight(), getWidth()); // copy accessible data over from other matrix
} // end Copy Constructor 


Matrix::Matrix(Matrix && m_other)
{
	// copy over members
	setHeight(m_other.getHeight());
	setWidth(m_other.getWidth());
	setCapacity(m_other.getCapacityH(), m_other.getCapacityW());
	b_transposed = m_other.b_transposed;

	this->dp_data = m_other.dp_data; // take array from other matrix

	// default members of the other matrix
	m_other.dp_data = nullptr;
	m_other.setHeight  (DEFAULT);
	m_other.setWidth   (DEFAULT);
	m_other.setCapacity(DEFAULT, DEFAULT);
	m_other.b_transposed = false;
} // end Move Constructor 


Matrix::~Matrix(void)
{
	// move assignment/constructor will call destructor, but there will be nothing to delete
	if (this->dp_data != nullptr)
	{
		deleteContents();
	} // end if
} // end method 


// Operations: 
size_t Matrix::getWidth(void) const
{
	// in transposed matrix, dimensions are swapped
	if (b_transposed)
	{
		return this->ui_height;
	} // end if
	else
	{
		return this->ui_width;
	} // end else
} // end method getWidth


size_t Matrix::getHeight(void) const
{
	// in transposed matrix, dimensions are swapped
	if (b_transposed)
	{
		return this->ui_width;
	} // end if
	else
	{
		return this->ui_height;
	} // end else
}  // end method getHeight


void Matrix::resize(size_t ui_h, size_t ui_w)
{
	// verify input
	ui_h = max(DEFAULT, ui_h);
	ui_w = max(DEFAULT, ui_w);

	printMatrix();

	resizeHelper(ui_h, ui_w); // call helper method
} // end method resize


void Matrix::transpose(void)      
{
	b_transposed = !b_transposed; // switch interpretation of the matrix
} // end method transpose


// Operators:
Matrix& Matrix::operator=(const Matrix & m_OTHER)
{
	// resize to dimensions of other matrix
	resize(m_OTHER.getHeight(), m_OTHER.getWidth());

	// copy over contents of other object
	copy(m_OTHER, getHeight(), getWidth());

	return *this;
} // end operator copy assignment


Matrix& Matrix::operator=(Matrix && m_other)
{
	if (this->dp_data != nullptr)
	{
		deleteContents(); // delete contents of this matrix
	} // end if

	// copy members from other matrix
	setHeight(m_other.getHeight());
	setWidth (m_other.getWidth ());
	setCapacity(m_other.getCapacityH(), m_other.getCapacityW());
	b_transposed = m_other.b_transposed;

	this->dp_data = m_other.dp_data; // take array from other matrix

	// default members of other matrix
	m_other.dp_data = nullptr;
	m_other.setHeight(DEFAULT);
	m_other.setWidth (DEFAULT);
	m_other.setCapacity(DEFAULT, DEFAULT);

	return *this;
} // end operator move assignment


double& Matrix::operator()(const size_t ui_ROW, const size_t ui_COL)
{
	// check if indices are in range
	if (ui_ROW >= getHeight() || ui_COL >= getWidth())
	{
		throw new out_of_range("Index out of range.");
	} // end if

	// in transposed matrix, dimensions are swapped
	if (b_transposed)
	{
		return dp_data[ui_COL][ui_ROW];
	} // end if
	else
	{
		return dp_data[ui_ROW][ui_COL];
	} // end else
} // end operator () 


double Matrix::operator()(const size_t ui_ROW, const size_t ui_COL) const
{
	// check if indices are in range
	if (ui_ROW >= getHeight() || ui_COL >= getWidth())
	{
		return std::numeric_limits<double>::signaling_NaN();
	} // end if

	// in transposed matrix, dimensions are swapped
	if (b_transposed)
	{
		return dp_data[ui_COL][ui_ROW];
	} // end if
	else
	{
		return dp_data[ui_ROW][ui_COL];
	} // end else
} // end operator () 


Matrix Matrix::operator+(const Matrix & m_OTHER) const
{
	// Variables:
	size_t w = min(this->getWidth() , m_OTHER.getWidth ()), // shrink dimensions as needed
	       h = min(this->getHeight(), m_OTHER.getHeight()); // for addition to work

	Matrix &sum = Matrix(h, w);

	
	for(size_t i = DEFAULT; i < h; i++)
	{
		for(size_t j = DEFAULT; j < w; j++)
		{
			sum(i,j) = this->operator()(i,j) + m_OTHER(i,j);
		} // end for j
	} // end for i

	return sum;
} // end operator +


Matrix& Matrix::operator+=(const Matrix & m_OTHER)
{
	// Variables:
	size_t w = min(this->getWidth() , m_OTHER.getWidth()) ,
	       h = min(this->getHeight(), m_OTHER.getHeight());


	// make matrix correct size
	if (w != getWidth() || h != getHeight())
	{
		this->resize(h, w);
	} // end if

	for(size_t i = DEFAULT; i < getHeight(); i++)
	{
		for(size_t j = DEFAULT; j < getWidth(); j++)
		{
			this->operator()(i, j) += m_OTHER(i,j);
		} // end for j
	} // end for i

	return *this;
} // end operator +=


Matrix Matrix::operator*(const Matrix & m_OTHER) const
{
	// Variables:
	Matrix &m_product = Matrix(this->getHeight(), m_OTHER.getWidth()); // product of the matrices

	size_t ui_temp = min(this->getWidth(), m_OTHER.getHeight()); // overlap of matrices


	for (size_t i = DEFAULT; i < m_OTHER.getWidth(); i++)
	{
		for (size_t j = DEFAULT; j < this->getHeight(); j++)
		{
			// Variables:
			double d_temp = DEFAULT; // storage for dot product

			
			// calculate dot product of the two vectors
			for (size_t k = DEFAULT; k < ui_temp; k++)
			{
				d_temp += this->operator()(j, k) * m_OTHER(k, i);
			} // end for k

			m_product(j, i) = d_temp; // add dot product to product matrix
		} // end for j
	} // end for i

	return m_product;
} // end operator *


Matrix& Matrix::operator*=(const Matrix & m_OTHER)
{
	// Variables:
	Matrix &m_temp = this->operator*(m_OTHER); // Make new matrix the product of this and other matrix


	// delete this matrix's contents
	if (dp_data != nullptr)
	{
		deleteContents();
	} // end if

	// move m_temp into this matrix
	setHeight(m_temp.getHeight());
	setWidth(m_temp.getWidth());
	setCapacity(m_temp.getCapacityH(), m_temp.getCapacityW());
	b_transposed = m_temp.b_transposed;

	// take values array from temp matrix
	this->dp_data = m_temp.dp_data;

	// default members of temp matrix
	m_temp.dp_data = nullptr;
	m_temp.setHeight(DEFAULT);
	m_temp.setWidth(DEFAULT);
	m_temp.setCapacity(DEFAULT, DEFAULT);
	m_temp.b_transposed = false;

	return *this;
} // end operator *= 


Matrix Matrix::operator*(const double d_VAL) const
{
	// Variables:
	Matrix &m_product = Matrix(getHeight(), getWidth()); // result matrix


	for(size_t i = DEFAULT; i < getHeight(); i++)
	{
		for(size_t j = DEFAULT; j < getWidth(); j++)
		{
			m_product(i,j) = this->operator()(i, j) * d_VAL;
		} // end for j
	} // end for i

	return m_product;
} // end operator *


Matrix& Matrix::operator*=(const double d_VAL)
{
	for(size_t i = DEFAULT; i < getHeight(); i++)
	{
		for(size_t j = DEFAULT; j < getWidth(); j++)
		{
			this->operator()(i, j) *= d_VAL;
		} // end for j
	} // end for i

	return *this;
} // end operator *=


bool Matrix::operator==(const Matrix & m_OTHER) const
{
	// check if object is being compared to itself
	if (this == &m_OTHER)
	{
		return true;
	} // end if

	// check if dimensions are equal
	if (m_OTHER.getHeight() != this->getHeight() || m_OTHER.getWidth() != this->getWidth())
	{
		return false;
	} // end if

	// check if corresponding elements are equal
	for (size_t i = DEFAULT; i < this->getHeight(); i++)
	{
		for (size_t j = DEFAULT; j < this->getWidth(); j++)
		{
			if (m_OTHER(i, j) != this->operator()(i, j))
			{
				return false;
			} // end if
		} // end for j
	} // end for i

	return true;
} // end operator == 


// instantiate helper
void Matrix::instantiate(double ** dp_arr, const size_t ui_SIZE)
{
	instantiate(dp_arr, ui_SIZE, ui_SIZE);
} // end helper method instantiate


// instantiates a new array of size i_HEIGHT x i_WIDTH and fills it with 0
void Matrix::instantiate(double ** dp_arr, const size_t ui_HEIGHT, const size_t ui_WIDTH)
{
	// make sure outer array has been created
	if (dp_arr == nullptr)
	{
		dp_arr = new double*[ui_HEIGHT];
	} // end if

	// fill inner arrays
	for (size_t i = DEFAULT; i < ui_HEIGHT; i++)
	{
		dp_arr[i] = new double[ui_WIDTH];
		memset(dp_arr[i], DEFAULT, ui_WIDTH * sizeof(double)); // initialize inner array to 0
	} // end for
} // end method instantiate


// copies other matrix's contents into this matrix
void Matrix::copy(const Matrix& m_OTHER, const size_t ui_HEIGHT, const size_t ui_WIDTH)
{
	for (size_t i = DEFAULT; i < ui_HEIGHT; i++)
	{
		for (size_t j = DEFAULT; j < ui_WIDTH; j++)
		{
			this->operator()(i, j) = m_OTHER(i, j);
		} // end for j
	} // end for i
} // end helper method copy


// decides whether resize is required
void Matrix::resizeHelper(const size_t ui_HEIGHT, const size_t ui_WIDTH)
{
	// if either height or width is 0, then nothing is accessible so there is no need to resize
	if (ui_HEIGHT == 0 || ui_WIDTH == 0)
	{
		// zero out entire matrix
		for (int i = DEFAULT; i < ui_capacityH; i++)
		{
			memset(dp_data[i], DEFAULT, ui_capacityW * sizeof(double));
		} // end for

		if (b_transposed)
		{
			setHeight(ui_WIDTH);           // height is always the accessible size of the outer array
			setWidth(ui_HEIGHT);           // width is always the accessible # of inner arrays
		} // end if
		else
		{
			setHeight(ui_HEIGHT);
			setWidth(ui_WIDTH);
		} // end else
	} // end if

	// check if new matrix will fit into current matrix
	else if ((ui_HEIGHT <= getCapacityH() && ui_WIDTH <= getCapacityW()))
	{ 
		if (b_transposed)
		{
			removeOld(ui_WIDTH, ui_HEIGHT); // zero out unused parts of matrix
			setHeight(ui_WIDTH);           // height is always the accessible size of the outer array
			setWidth(ui_HEIGHT);           // width is always the accessible # of inner arrays
		} // end if
		else
		{
			removeOld(ui_HEIGHT, ui_WIDTH); // zero out unused parts of matrix
			setHeight(ui_HEIGHT);
			setWidth(ui_WIDTH);
		} // end else
	} // end elif

	else  // matrix needs to be resized
	{
		resizeMatrix(ui_HEIGHT, ui_WIDTH);
	} // end else
} // end method resizeHelper


// resizes matrix to new dimensions
void Matrix::resizeMatrix(const size_t ui_HEIGHT, const size_t ui_WIDTH)
{
	// Constants:
	const size_t ui_OLD_H = min(ui_HEIGHT, this->getHeight()), // for copying over old data
			     ui_OLD_W = min(ui_WIDTH, this->getWidth());

	// Variables:
	double ** dp_tempData; // new data array

	size_t ui_newH = ((ui_HEIGHT > 5500) ? ui_HEIGHT : (ui_HEIGHT * 2)), // to avoid running out of memory
		   ui_newW = ((ui_WIDTH  > 5500) ? ui_WIDTH  : (ui_WIDTH  * 2)); // with large matrices


	dp_tempData = new double*[ui_newH];
	instantiate(dp_tempData, ui_newH, ui_newW);

	// copy over old matrix's contents into new matrix
	for (int i = DEFAULT; i < ui_OLD_H; i++)
	{
		for (int j = DEFAULT; j < ui_OLD_W; j++)
		{
			dp_tempData[i][j] = this->operator()(i,j);
		} // end for j
	} // end for i

	b_transposed = false; // after resize matrix will not be transposed

	// delete old contents of this matrix
	deleteContents();

	// set dimensions
	setHeight(ui_HEIGHT);
	setWidth(ui_WIDTH);
	setCapacity(ui_newH, ui_newW);

	this->dp_data = dp_tempData;
} // end method resizeWeird


// zeroes out unused portions of the matrix after resize
void Matrix::removeOld(const size_t ui_HEIGHT, const size_t ui_WIDTH)
{
	// Variables:
	int h = min(ui_height, ui_capacityH), // height/width could be larger than capacity 
		w = min(ui_width, ui_capacityW);  // iff resize(0,n) or resize(n,0) was called previously


	// set all rows between new height and old height to 0
	if (h > ui_HEIGHT)
	{
		for (int i = ui_HEIGHT; i < h; i++)
		{
			memset(dp_data[i], DEFAULT, getWidth()*sizeof(double));
		} // end for
	} // end if

	// set all columns between new width and old width to 0
	if (w > ui_WIDTH)
	{
		for (int i = DEFAULT; i < ui_HEIGHT; i++)
		{
			for (int j = ui_WIDTH; j < w; j++)
			{
				dp_data[i][j] = DEFAULT;
			} // end for j
		} // end for i
	} // end if
} // end method removeOld


// deallocates all dynamic memory used by this matrix
void Matrix::deleteContents(void)
{
	// destructor is called after some move operations when there's nothing to delete
	if (this->dp_data != nullptr)
	{
		// get rid of this object's data
		for (int i = DEFAULT; i < getCapacityH(); i++)
		{
			delete[] this->dp_data[i];
		} // end for

		delete[] this->dp_data;
	} // end if
} // end method deleteContents


// prints the entire matrix for testing
void Matrix::printMatrix(void)
{
	for (int i = 0; i < ui_capacityH; i++)
	{
		for (int j = 0; j < ui_capacityW; j++)
		{
			std::cout << dp_data[i][j] << " ";
		} // end for j
		std::cout << std::endl;
	} // end for i
	std::cout << std::endl;
} // end method printMatrix


// Setters:
inline void Matrix::setHeight(const size_t ui_HEIGHT)
{
	this->ui_height = ui_HEIGHT;
} // end method setHeight


inline void Matrix::setWidth(const size_t ui_WIDTH)
{
	this->ui_width = ui_WIDTH;
} // end method setWidth


inline void Matrix::setCapacity(const size_t ui_CAPACITY_H, const size_t ui_CAPACITY_W)
{
	ui_capacityH = ui_CAPACITY_H;
	ui_capacityW = ui_CAPACITY_W;
} // end method setCapacity


// Getters:
inline size_t Matrix::getCapacityH(void)
{
	return this->ui_capacityH;
} // end method getCapacityH


inline size_t Matrix::getCapacityW(void)
{
	return this->ui_capacityW;
} // end method getCapacityW