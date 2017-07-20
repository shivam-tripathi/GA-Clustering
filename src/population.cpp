#include "population.h"

Population :: Population(Data &data, int n) {
	this->data = &(data);
	for(int i=0; i<n; i++) {
		Chromosome chromo(data);
		solutions.push_back(Solution(&chromo));
		printf("Chromosome %d populated \n", i+1);
	}
}
