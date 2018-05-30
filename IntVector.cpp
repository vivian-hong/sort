#include <iostream>
#include "IntVector.h"
#include <stdexcept>

using namespace std;

/*
 * A constructor
 */
IntVector::IntVector()
{
	vector_size = 0;
	vector_capacity = 0;
	vector = NULL;
}

/*
* A constructor with an initial size
*/
IntVector::IntVector(int initialSize)
{
	vector_size = initialSize;
	vector_capacity = initialSize;
	vector = new int[initialSize];
	for (int i = 0; i<initialSize; i++){
		vector[i] = 0;
	}
}

/*
* A copy constructor
*/
IntVector::IntVector(const IntVector &source)
{
	copy(source.vector);
}

/*
 * An assignment operator
 */
IntVector &IntVector::operator=(const IntVector &rhs)
{
	if (this != &rhs){
		delete[] vector;
		vector = new int[rhs.size()];
		vector_size = rhs.vector_size;
		vector_capacity = rhs.vector_capacity;
		copy(rhs.vector);
	}
	return *this;
}

/*
 * Purpose: copy an array into the vector array
 * Arguments: int array to be copied
 * Returns: none
 */
void IntVector::copy(int *copy_vector) const
{
	for (int i = 0; i < vector_size; i++){
		vector[i] = copy_vector[i];
	}
}

/*
 * A destructor
 */
IntVector::~IntVector()
{
	delete[] vector;
}

/*
* Makes the vector have a size and capacity of 0 and
* recycles heap-allocated storage.
* The client may continue to use the IntVector after
* calling destroy, e. g., they could add elements to it.
*/
void IntVector::destroy()
{
	vector_size = 0;//for many implementations more efficient than deleting
			//entire array
}

/*
* Purpose: Return integer value at given index.
*
* Throw exception or abort with error message if index
* out of range.
* Arguments: int representing the index of the array of the desired value
* Returns: int value at the index of the array
*/
int IntVector::get(int index) const
{
	if (index >= vector_size){
		throw runtime_error("Index out of bounds");
	}
	return vector[index];
}

/*
* Purpose: Set array element at given index to newVal.
*
* Throw exception or abort with error message if index
* out of range.
* Arguments: int index of the array and int new value to set index to
* Returns: none
*/
void IntVector::set(int index, int newVal)
{
	if (index >= vector_size){
		throw runtime_error("Index out of bounds");
	}
	vector[index] = newVal;
}

/*
* Purpose:Return reference to array slot at given index.
* This permits subscripted access to vector as
* L-value and/or R-value.
*
* Throw exception or abort with error message if index
* out of range.
* Arguments: int for index desired
* Returns: int in form that could assign to
*/
int &IntVector::operator[](int index) const
{
	if (index >= vector_size){
		throw runtime_error("Index out of bounds");
	}
	return vector[index];
}

/*
 * Purpose: Add newVal to end of vector, increasing current size by one.
 * Arguments: int value to add
 * Returns: none
 */
void IntVector::add(int newVal)
{
	if (vector_size == vector_capacity){
		expand();
	}
	vector[vector_size] = newVal;
	vector_size++;
}

/*
 * Purpose: Return current size of vector.
 * Arguments: none
 * Returns: int of size of array- size being the number of spots in the array
 */
int IntVector::size() const
{
	return vector_size;
}

/*
 * Purpose: Return current capacity of vector
 * Arguments: none
 * Returns: int of capacity of array
 */
int IntVector::capacity() const
{
	return vector_capacity;
}

/*
 * Purpose: expand the dynamic array
 * Arguments: none
 * Returns: none
 */
void IntVector::expand()
{
	vector_capacity = vector_capacity * 2 + 1;
	int *bigger_array = new int[vector_capacity];
	for (int i = 0; i<vector_size; i++){
		bigger_array[i] = vector[i];
	}
	delete[] vector;
	vector = bigger_array;
}
