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
	Chromosome crossover();
	void cross_clusters(int, int);
	void compute();
	void populate();
	void print_chromosome();
};

bool cmp(Chromosome &, Chromosome &);

#endif // __CHROMOSOME_H__