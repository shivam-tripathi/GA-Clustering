#ifndef __POPULATIONH__
#define __POPULATIONH__

#include "chromosome.h"
#include "data.h"

struct Solution{
	Chromosome *chromosome;
	int domination_count;
	std::vector<int> dominated_solutions;
	Solution(Chromosome *chromo) {
		chromosome = chromo;
		domination_count = 0;
	}
};

class Population {
public:
	Data *data;
	std::vector<Solution> solutions;

	Population(Data &, int);
};

struct Cmp {
	bool operator() (Solution &a, Solution &b) const {
		return a.domination_count < b.domination_count;
	}
};

#endif // __POPULATIONH__