/*
 *  Comp 15
 *  Sorting Assignment
 *
 *  sortnums.cpp
 *  Author:  Mark A. Sheldon, Tufts University, Spring 2016
 */
#include <iostream>
#include <cstdlib>

#include "IntVector.h"

using namespace std;

string algorithmFromCommandLine(int argc, char *argv[]);
void   usageAbort (string progname, string message);
void   readNumbers(istream &input, IntVector &data);
void   sortNumbers(string algorithm, IntVector &data);
void   printNumbers(const IntVector &data);

void swap(IntVector &vector, int i, int j);
void bubbleSort(IntVector &data);
void quickSort(IntVector &data, int left, int right);
void radixSort(IntVector &data);
int power(int base, int exponenet);


int main(int argc, char *argv[])
{
        IntVector data;
        string    sortAlgorithm = algorithmFromCommandLine(argc, argv);
        readNumbers(cin, data);
        sortNumbers(sortAlgorithm, data);
        printNumbers(data);

        return 0;
}

/*
 * Abort the program with a message on standard error
 * explaining how to run the program correctly from the 
 * command line.
 */
void usageAbort(string progname, string message)
{
        cerr << message << endl
             << "Usage:  " << progname << " algorithm" << endl
             << "     where algorithm is one of "
             << "bubble, sort2, or sort3"
             << endl;
        exit(1);
}

/***************************************************************************/
/**                      Functions you may want to write                  **/
/***************************************************************************/

//Return sorting algorithm specified on command line.
//Abort program if no algorithm is specified or if specified
//algorithm is not supported.
string algorithmFromCommandLine(int argc, char *argv[])
{
	if (argc < 2){
		usageAbort("no", "Error: no algorithm specified");
		return " ";
	}
	else if (argv[1] == string("bubble")){
		return "bubble";
	}
	else if (argv[1] == string("sort2")){
		return "quick";
	}
	else if (argv[1] == string("sort3")){
		return "radix";
	}
	else{
		usageAbort(argv[1], "Error: specified "
				"algorithm is not supported");
		return " ";
	}
}


/*
* Read in a collection of integers from the given input stream
* and add them to the end of the data vector.  Input numbers are
* separated by whitespace (they don't have to be one per line).
*
* My implementation does not distinguish between failure due to end
* of file or any other failure of the input device.  Yours may do
* likewise.
*/
void readNumbers(istream &input, IntVector &data)
{
	int i;
	while (input>>i){//use this instead of eof becuase eof checks after
		//if (!isspace(i) and !cin.fail()){
			data.add(i);
		//}
	}
}

/*
* Updates contents of data so items are sorted using the chosen
* algorithm.
*/
void sortNumbers(string algorithm, IntVector &data)
{
	if (algorithm == "bubble"){
		bubbleSort(data);
	}
	else if (algorithm == "quick"){;
		quickSort(data, 0, data.size()-1);
	}
	else if (algorithm == "radix"){
		radixSort(data);
	}
}


/*
* Print contents of data one item per line.
*/
void printNumbers(const IntVector &data)
{
	for (int i = 0; i<data.size(); i++){
		cout<< data.get(i)<<endl;
	}
}

/*
* Updates the given vector so that the items at position i and j
* are swapped.
*/
void swap(IntVector &vector, int i, int j)
{
	int first_item = vector.get(i);
	int second_item = vector.get(j);
	vector.set(i, second_item);
	vector.set(j, first_item);
}

/*
* Purpose: In-place sort of contents of data using the bubble sort algorithm.
* Arguments: IntVector with array to be sorted
* Returns: None
*/
void bubbleSort(IntVector &data)
{
	int num_swap = 0; //counts swaps to see if a list is correctly sorted
	for (int i = data.size(); i>0; i--){
		num_swap = 0;
		for (int j = 0; j<i-1; j++){
			if (data.get(j)>data.get(j+1)){
				swap(data, j, j+1);
				num_swap++;
			}
		}
		if (num_swap == 0){
			break;
		}
	}
}
/*
 * Purpose: Recursive in-place sort of contents of data using the quick sort
 * 	    algorithm
 * Arguments: IntVector with array to be sorted and two ints representing the
 * 	      bounds of the sort
 * Returns: None
 */
void quickSort(IntVector &data, int left, int right)
{
	int l = left;
	int r = right;
	int pivot = (r + l)/2; 	//uses index in middle, more efficient in
				//already sorted arrays and arrays with
				//repeating elements
	//no need for base case because if l == r, they're incremented and
	//decremented accordingly

	//to ensure pivot doesn't get moved:
	swap(data, pivot, l);
	pivot = l;
	l++;
	while (l <= r){
		while (data.get(l) < data.get(pivot) and l < data.size()-1){
			l++;
		}
		while (data.get(r) > data.get(pivot)){
			r--;
		}
		if (l <= r){
			swap(data, r, l);
			l++;
			r--;
		}
	}
	swap(data, pivot,l-1);//places pivot in correct spot
	if (left < r){
		quickSort(data, left, r);
	}
	if (l < right){
		quickSort(data, l, right);
	}
}
/*
 * Purpose: Out-of-place sort of contents of data using the radix sort
 * 	    algorithm
 * Arguments: IntVector containing array to be sorted
 * Returns: None
 */
void radixSort(IntVector &data)
{
	IntVector *temp = new IntVector(data.size());
	int max = 0;
	for (int i = 0; i < data.size(); i++){
		if (data.get(i) > max){
			max = data.get(i);
		}
	}
	int num_digits = 0;
	while ((max/power(10,num_digits)) > 1){
		num_digits++;
	}
	int pass = 0;
	while (pass < num_digits){
		IntVector bin[10];
		for (int i = 0; i < data.size(); i++){
			int index = (data.get(i)/power(10,pass)) % 10;
			bin[index].add(data.get(i));
		}
		int i = 0;
		for (int j = 0; j < 10; j++){
			for (int k = 0; k<bin[j].size(); k++){
				temp->set(i, bin[j].get(k));
				i++;
			}
		}
		for (int i = 0; i < 10; i++){
			bin[i].destroy();
		}
		for (int i = 0; i < data.size(); i++){
			data.set(i, temp->get(i));
		}
		pass++;
	}
	delete temp;
}
/*
 * Purpose: Compute and int to the power of another int (pow function in math.h
 * 	    returns a double or float and not an int
 * Arguments: two ints, the base and exponent
 * Returns: int representing the value of base to the power of exponent
 */
int power( int base, int exponent)
{
	int pow = 1;
	for (int i = 0; i<exponent; i++){
		pow *= base;
	}
	return pow;
}
