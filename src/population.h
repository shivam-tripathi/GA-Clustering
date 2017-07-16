#ifndef __POPULATIONH__
#define __POPULATIONH__

#include "chromosome.h"
#include "data.h"

class Population {
public:
	Data *data;
	std::vector<Chromosome> chromosomes;

	Population(Data &, int);
	Population(std::vector<Chromosome> &);
	void populate(int n);
};

#endif // __POPULATIONH__