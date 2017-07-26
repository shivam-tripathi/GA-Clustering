#include "population.h"

Population :: Population(Data &data, int n) {
	this->data = &(data);
	solutions.clear();
	for(int i=0; i<n; i++) {
		Chromosome *chromo = new Chromosome(data);
		solutions.push_back(Solution(chromo, i));
		// printf("\t\t%lu ->\t%f %d ==> %d \n", solutions.size(), solutions[i].chromosome->mean, solutions[i].chromosome->clusters_count, solutions[i].index);
		// print_population();
		printf("Chromosome %d populated \n", i+1);
		printf("\n\n");
	}
}

void Population :: print_population() {
	for (int i=0; i<solutions.size(); i++) {
		printf("Printing population --> \t\t\t%f %d ==> %d \n", solutions[i].chromosome->mean, solutions[i].chromosome->clusters_count, solutions[i].index);
		// print_chromosome((solutions[i].chromosome));
		// printf("\n");
	}
}