#ifndef __NSGA_2__
#define __NSGA_2__


#include "population.h"


// Utility sorting structure for each solution, used to assign each instance various fronts.
// Apart from index indentifier, it stores:
//		1. Domination count (the number of solutions which dominate the solution)
//		2. Distance
// 		3. Domination set (index of solutions that this solution dominates)
struct Sorting {
	int index;
	int domination_count;
	float distance;
	std::vector<int> domination_set;
	Sorting(int index, int dominated_count, float distance) :
	index(index), domination_count(dominated_count), distance(distance)
	{}
};



// Compare functor to sort instances according to (and by precedence) (according to NSGA2):
// 		1. Domination count (the number of solutions which dominate the solution)
//		2. Distance ()
struct CmpSorting {
	bool operator() (const Sorting &a, const Sorting &b) {
		if (a.domination_count != b.domination_count)
			return a.domination_count < b.domination_count;
		if (a.distance != b.distance)
			return a.distance > b.distance;
		return a.index < b.index;
	}
};


// Structure to store details of the value of the objective function for an instance
// Index indentifies the chromosome number, and value sets the value.
// Objectives for this case is:
// 		1. Minimise sum of average distances of cluster elements to cluster centre
// 		2. Minimise the number of clusters
struct Objective {
	int index;
	float value;
	Objective(int i, int k) :
	index(i), value(k)
	{}
};


// Compare functor to sort set of instance by their objective value
// In this case, we need to reduce both the objectives: and hence
struct CmpObjective {
	bool operator() (const Objective &a, const Objective &b) {
		if (a.value != b.value)
			return a.value > b.value;
		return a.index < b.index;
	}
};


// ??
struct CmpErase {
	bool operator() (const Sorting &a, const Sorting &b) {
		return a.index < b.index;
	}
};


// Base class for NSGA2 algorithm
// This class simply sorts the population object passed to it
// It approaches the problem in a non destructive way, using Sorting structure
// The Sorting structure initially stores the objective values of all related functions and index
// The vector of sorting structure is used then to produce sorted indexes of the chromosomes
// Using sorting vector as base, the original population is rearranged such that it is ordered
// in descending order of priority.
// This modified population object then can be used for crossovers.
// Thus it provides and abstraction of NSGA2 making it completely independent of input population object
// and other GA details.
// Objective functions have been tuned according to this problem, so inorder to use this code piece,
// one would have to take care of objective functions occurences in this file and associated cpp file.
// After that simply run it to get desired results.
class NSGA2 {
public:

	Population &population;
	int solution_count;
	std::vector<Sorting> sorting;
	// std::vector<Chromosome> final;

	NSGA2(Population &);
	// Flushes the sorting state
	void reset();
	// Sets the index of the population object chromosomes in the order they are arranged
	void set();
	// Computes distance
	void set_distance();
	// Computes domination
	void set_domination();
	void sort();
};

#endif // __NSGA_2__