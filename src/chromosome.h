#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "data.h"


// Base class to store Chromosomes in the function
class Chromosome {
public:
	int index;
	int element_count;
	Data &data;
	std::vector<node> nodes;
	std::vector<cluster> clusters;
	int clusters_count;
	float mean;

	Chromosome(Data &, int);
	Chromosome(const Chromosome &);
	void operator = (const Chromosome &);
	void compute();
	void populate();
};

bool cmp(Chromosome &, Chromosome &);
void print_chromosome(Chromosome *);

#endif // __CHROMOSOME_H__