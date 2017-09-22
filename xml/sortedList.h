#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <list>
#include <math.h>

// SortedList with functions of 
// - inserting ceratain pair in list with saving its sorting
// - deleting nested elements to ensure that sortedList isn't containing repeating elements
// - excretion primes numbers in list intervals
class SortedList
{

public:
	// list consisting of intervals
	// first member of pair is number - limit of interval
	// second member of pair is designation of started or ended limit is
	std::list<std::pair<int, bool>> list;

	// Function for inserting pair in list with saving its sorting
	void push(int a, bool b);

	// Delete nested elements to ensure that this->list intervals
	// don't consist repeating intervals
	void deleteNested();

	// Excretion prime numbers in list intervals
	std::list<int> primesInList();

private:

	// Check if n is prime number
	bool isPrime(int n);

};

#endif // SORTED_LIST_H
