#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "data.h"

class Chromosome {
public:
	int element_count;
	Data *data;
	std::vector<node> nodes;
	std::vector<cluster> clusters;
	int clusters_count;
	Chromosome(Data &);
	void populate();
};

#endif // __CHROMOSOME_H__