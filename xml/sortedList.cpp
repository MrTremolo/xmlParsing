#include "sortedList.h"

// Function for inserting pair in list with saving its sorting
void SortedList::push(int a, bool b)
{
	// If list is empty
	if (!list.size())
		list.push_back(std::make_pair(a, b));

	// Else find the place to inserting
	else
	{
		
		for (auto i = list.begin(); i != list.end(); i++)
		{
			if (i->first >= a)
			{
				list.insert(i, std::make_pair(a, b));
				return;
			}
		}
		list.push_back(std::make_pair(a, b));
	}
}

// Delete nested elements to ensure that this->list intervals
// don't consist repeating intervals
void SortedList::deleteNested()
{
	// j - index of intervals repeats
	int j = 0;

	// i - first iterator of list
	// k - iterator next after i
	auto i = list.begin(), k = i;
	++k;
	for (; i != list.end();)
	{

		// If i->second is left limit
		if (i->second)
		{
			++j;
		}

		// If more than 1 repeating delete excess intervals
		if (j > 1)
		{
			// If i->second is right limit
			if (!i->second)
			{
				--j;
			}

			// Erase excess limit and shfit the iterator i to k
			list.erase(i);
			i = k;
			++k;
		}

		// Else shift iterators
		else
		{
			// If i->second is right limit
			if (!i->second)
			{
				--j;
			}
			++i;
			// Ensure that k+1 is not pointer to memory after list.end() iterator
			if (k != list.end())
				++k;
		}
	}
}

// Excretion prime numbers in list intervals
std::list<int> SortedList::primesInList()
{
	std::list<int> lst;

	// a - is lift limit of interval
	// b - is right limit of interval
	auto a = list.begin();
	auto b = a;
	++b;
	for (;;)
	{
		// Find primes within interval
		for (int i = a->first; i <= b->first; i++)
		{
			if (isPrime(i))
				lst.push_back(i);
		}

		// Step out 
		// Ensure that incremented a isn't point on list.end()
		++a, ++a;
		if (a == list.end())
			break;
		++b, ++b;
	}
	return lst;
}

// Check if n - is prime number
bool SortedList::isPrime(int n)
{
	// 1, 0 and negative numbers are not primes
	if (n <= 1)
		return false;

	// 2 and 3 are primes
	else if (n < 4)
		return true;
	else if (n % 2 == 0)
		return false;

	// We have already excluded 4, 6 and 8
	else if (n < 9)
		return true;
	else if (n % 3 == 0)
		return false;
	else
	{
		// sqrt(n) rounded to the greatest int that can be dividere of n
		double r = floor(sqrt(n));
		int f = 5;

		// All primes greater than 3 can be written in the form 6k+/-1
		while (f <= r)
		{
			if (n % f == 0)
				return false;
			if (n % (f + 2) == 0)
				return false;
			f += 6;
		}
	}

	// In other cases
	return true;
}