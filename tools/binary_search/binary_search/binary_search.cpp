// binary_search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

template<typename Iter>
Iter binarySearch(Iter beg, Iter end, const typename Iter::value_type &v)
{
	Iter first = beg;
	Iter last = end;
	
	while(first != last) {
		Iter mid = first;
		advance(mid, distance(first, last) / 2);
		if (!(*mid < v)) {
			last = mid;
		}
		else {
			first = mid + 1;
		}

		if (first == end) {
			break;
		}

		if (*first == v) {
			return first;
		}
	}

	return end;

}


using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	vector<int> ints;
	ints.push_back(1);
	ints.push_back(2);
	ints.push_back(3);
	ints.push_back(4);
	ints.push_back(6);	
	ints.push_back(7);
	ints.push_back(8);
	ints.push_back(9);
	ints.push_back(10);

	assert(binarySearch(ints.begin(), ints.end(), 3)  != ints.end());
	assert(binarySearch(ints.begin(), ints.end(), 8)  != ints.end());

	assert(binarySearch(ints.begin(), ints.end(), 1)  != ints.end());
	assert(binarySearch(ints.begin(), ints.end(), 10) != ints.end());

	assert(binarySearch(ints.begin(), ints.end(), 0)  == ints.end());
	assert(binarySearch(ints.begin(), ints.end(), 5)  == ints.end());
	assert(binarySearch(ints.begin(), ints.end(), 99) == ints.end());
	
	cout << "Good!!!!" << endl;

	return 0;
}

