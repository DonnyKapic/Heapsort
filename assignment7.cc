/*********************************************************************
NAME: Dajan Kapic
ASSIGNMENT: Assignment 7 Heaps and Heapsort
DUE DATE: April 3, 2019
ZID: Z1855273
PURPOSE: This program sorts numbers using the heapsort technique.
	 It firsts builds a heap structur for the numbers. Then, it
	 retrieves these numbers from the heap in a certain order and
	 prints them out on stdout.
*********************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

void build_heap (vector<int>&, int, bool (*compar)(int, int));
void heapify (vector<int>&, int, int, bool (*compar)(int, int));
bool less_than (int, int);
bool greater_than (int, int);
void heap_sort (vector<int>&, int, bool (*compar)(int, int));
int extract_heap (vector<int>&, int&, bool (*compar)(int, int));
void print_vector (vector<int>&, int, int);

const int HEAP_SIZE = 50;

int main(int argc, char** argv) {
    // ------- creating input vector --------------
    vector<int> v;
    v.push_back(-1000000);    // first element is fake
    for (int i=1; i<=HEAP_SIZE; i++)
        v.push_back( i );
    random_shuffle( v.begin()+1, v.begin()+HEAP_SIZE+1 );

    cout << "\nCurrent input numbers: " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing min heap ------------------
    cout << "\nBuilding a min heap..." << endl;
    build_heap(v, HEAP_SIZE, less_than);
    cout << "Min heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, less_than);
    cout << "Heap sort result (in ascending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing max heap ------------------
    cout << "\nBuilding a max heap..." << endl;
    build_heap(v, HEAP_SIZE, greater_than);
    cout << "Max heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, greater_than);
    cout << "Heap sort result (in descending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    return 0;
}

/*******************************************************************
build_heap
Parameters: 1. A reference to a vector
	    2. Size of heap
	    3. A function pointer to compare two integers
Purpose: This function contructs a heap with heap_size elements in
	 the vector v.
*******************************************************************/
void build_heap (vector<int>& v, int heap_size, bool (*compar)(int , int)){
	for (int i = heap_size/2; i >= 1; i--){
		heapify(v, heap_size, i, compar);
	}
}

/******************************************************************
heapify
Parameteres: 1. A reference to a vector
	     2. Size of heap
	     3. Iterator
	     4. A function pointer to compare two integers
Purpose: This function "heapifies" a tree at the root position r
	 assuming r's two sub-trees are already heaps.
******************************************************************/
void heapify (vector<int>& v, int heap_size, int r, bool (*compar)(int , int )){
	int L = 2*r;
	int R = 2*r+1;
	int largest;
	if (L <= heap_size && compar(v[L], v[r]))
		largest = L;
	else
		largest = r;
	if (R <= heap_size && compar(v[R], v[largest]))
		largest = R;
	if (largest != r){
		// swap v[r] & v[largest]
		int temp = v[r];
		v[r] = v[largest];
		v[largest] = temp;
		heapify(v, heap_size, largest, compar);
	}
}

/****************************************************************
less_than
Parameters: 1 & 2. Integers to be compared
Purpose: Returns true if x is less than y
****************************************************************/
bool less_than (int x, int y){
	if (x < y)
		return true;
	else
		return false;
}

/******************************************
greater_than
Parameters: 1 & 2. Integers to be compared
Purpose: Returns true if x is greater than y
******************************************/
bool greater_than (int x, int y){
	if (x > y)
		return true;
	else
		return false;
}

/*************************************************************
heap_sort
Paramters: 1. A reference to a vector
	   2. Size of heap
	   3. A function pointer to compare two integers
Purpose: This function implements heap sort algorithm.
*************************************************************/
void heap_sort (vector<int>& v, int heap_size, bool (*compar)(int, int )){
	build_heap(v, heap_size, compar);
	for (int i = heap_size; i >= 2; i--){
		//swap v[1] and v[i]
		int temp = extract_heap(v, heap_size, compar);
		v[heap_size + 1] = temp;
	}
	reverse(v.begin()+1, v.end());
}

/*************************************************************
extract_heap
Parameters: 1. A reference to a vector
	    2. Reference to size of heap
	    3. A function pointer to compare two integers
Purpose: This function extracts the root of the heap recorded
	 in v, fills the root with the last element of current
	 heap, updates heap_size, "heapifies" at the root, and
	 returns the old root value.
*************************************************************/
int extract_heap (vector<int>& v, int& heap_size, bool (*compar)(int, int)){
	int max = v[1];
	v[1] = v[heap_size];
	heap_size -= 1;
	heapify(v, heap_size, 1, compar);
	return max;
}

/************************************************************
print_vector
Parameters: 1. A reference to a vector
	    2. Position in vector
	    3. Number of elements to print
Purpose: Displays "size" number of elements containted in
	 vector v starting at position "pos"
************************************************************/
void print_vector (vector<int>& v, int pos, int size){
	int row = 0;
	for(int i = pos; i <= size; i++){
		cout << setw(5) << v[i];
		row++;
		if (row % 8 == 0)
			cout << endl;
	}
	cout << endl;
}
