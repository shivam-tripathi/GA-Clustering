#ifndef __NSGA_2__
#define __NSGA_2__

#include "population.h"

class NSGA2 {
public:
	Population *population;
	std::vector<Solution> sorted_fronts;

	NSGA2(Population *);
	void sort();
};

#endif // __NSGA_2__