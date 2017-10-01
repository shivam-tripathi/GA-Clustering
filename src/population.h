#ifndef __POPULATIONH__
#define __POPULATIONH__


#include "chromosome.h"
#include "data.h"


// struct Solution{
// 	Chromosome *chromosome;
// 	int index;
// 	float distance;
// 	int domination_count;
// 	std::vector<int> dominated_solutions;
// 	Solution(Chromosome *chromo, int i) {
// 		index = i;
// 		chromosome = chromo;
// 		distance = 0;
// 		domination_count = 0;
// 	}
// };


// Base class to store Population
class Population {
public:
	Data &data;
	// std::vector<Solution> _solutions;
	std::vector<Chromosome> solutions;

	Population(Data &, int);
	void print_population();
	void reset_index();
	void crossover();
};

// struct CmpSolution {
// 	bool operator() (Solution &a, Solution &b) const {
// 		if (a.domination_count != b.domination_count)
// 			return a.domination_count > b.domination_count;
// 		return a.distance > b.distance;
// 	}
// };

#endif // __POPULATIONH__