#ifndef __NSGA_2__
#define __NSGA_2__

#include "population.h"

struct Sorting {
	int domination_count;
	float distance;
	int index;
	Sorting(int index, int dominated_count, float distance) :
	index(index), domination_count(dominated_count), distance(distance)
	{}
};

struct CmpSorting {
	bool operator() (const Sorting &a, const Sorting &b) {
		if (a.domination_count != b.domination_count)
			return a.domination_count < b.domination_count;
		if (a.distance != b.distance)
			return a.distance > b.distance;
		return a.index < b.index;
	}
};

struct Objective {
	int index;
	float value;
	Objective(int i, int k) :
	index(i), value(k)
	{}
};

struct CmpObjective {
	bool operator() (const Objective &a, const Objective &b) {
		if (a.value != b.value)
			return a.value > b.value;
		return a.index < b.index;
	}
};

struct CmpErase {
	bool operator() (const Sorting &a, const Sorting &b) {
		return a.index < b.index;
	}
};

class NSGA2 {
public:
	Population *population;
	int solution_count;

	NSGA2(Population *);
	void sort(int);
	void set_distance();
	void set_domination_count();
};

#endif // __NSGA_2__