#ifndef __NSGA_2__
#define __NSGA_2__

#include "population.h"

struct Sorting {
	int domination_count;
	int index;
	Sorting(int dominated_count, int index) :
	domination_count(dominated_count), index(index)
	{}
};

struct CmpSorting {
	bool operator() (const Sorting &a, const	Sorting &b) {
		if (a.domination_count != b.domination_count)
			return a.domination_count > b.domination_count;
		return a.index < b.index;
	}
};

class NSGA2 {
public:
	Population *population;
	int solution_count;

	NSGA2(Population *);
	void sort();
};

#endif // __NSGA_2__