## ReadMe for COMP 15 HW5
## Sorting Assignment

Purpose of the Program:

- sorts integers from a file (given by the user) from small to large
- accepts a command line parameter detailing which algorithm the program
  should use - either bubble, quick, or radix
- reads in a sequence of integers to be sorted from standard input (cin)
- prints the sorted list of integers, one integer per line, on standard 
  output (cout)

List of Files:

IntVector.cpp -- holds all the functions for the IntVector class including add,
		 size, get, set, capacity, expand (private), etc.
IntVector.h -- header function for IntVector.cpp
sortnums.cpp -- holds main and three sorts as well as helper functions for the 
		the sorts.

How to Compile:

  Use included makefile.

Outline of Data Structure:

- IntVector class that holds a dynamic array, functions to manipulate it, and 
  variables associated with it (size, capacity)
- Functions in sortnums.cpp create instances of IntVector class to hold the data
  input and to assist in sorting in radix sort (bins are arrays of IntVectors, 
  i.e. the array holds objects that contain dynamic arrays)

Outline of Algorithm:

- Bubble Sort:
	- sorting algorithm involves iterating through list repeatedly and
	  switching items that are next to each other if they are in the wrong
	  order
	- worst case complexity would be O(n^2) if the list is in reverse order
	  because the list would be iterated through every time
	- best case complexity would be O(n) if the list is already in order
	  because bubble sort checks for if the list is in order, so it would 
	  only iterate through once
- Quick Sort:
	- sorting algorithm that chooses a pivot point in the array and orders
	  the array so that all smaller numbers come before the pivot point and
	  all larger numbers come after the pivot point (partitioning)- the
	  function is then called recursively on the two separated lists of 
	  smaller and larger numbers
	- the base case for the recursion are lists of one or fewer elements
	- the worst case time complexity would be O(n^2) which occurs when the
	  partitioning divides the list into the least balanced pieces (0 and
	  n-1) which can happen if the pivot is the smallest or largest element
	  on the list
	- the best case time complexity would be 0(n log(n)) which occurs when 
	  the most balanced case happens (i.e. each partition divides the list
	  into equal pieces) this each recursive call goes through a list of 
	  half the size.
- Radix Sort:
	- sorting algorithm that passes through each digit (starting with the 
	  ones digit) of a number and puts them in bins with a particular value
	  that matches the digit being looked at from each number
	- between passes, place the numbers back in the array in the order that
	  the were in the bins 
	- worst case complexity = best case complexity = O(dn) for d digits 
	  because there is a pass for each digit and during each pass, go 
	  through the entire list

List of references for algorithms of sorts:
	- used Wikipedia pages for all