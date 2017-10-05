#ifndef __POPULATIONH__
#define __POPULATIONH__

#include "chromosome.h"
#include "data.h"


// Base class to store Population
class Population {
public:
	std::vector<Chromosome> solutions;

	Population(Data &, int);
	void print_population();
	void reset_index();
	void crossover(int);
	void mutation();
};

#endif // __POPULATIONH__