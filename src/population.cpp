#include "population.h"


Population :: Population(Data &data, int n) : data(data) {
	// Initialise population's data, clean solutions vector (incase already filled)
	// this->data = &(data);
	solutions.clear();

	// Add chromosomes to the solutions vector
	// n is the number of chromosomes, sent as arguments from the main function
	printf("\nAdding chromosomes to the population ...\n\n");
	for(int i=0; i<n; i++) {
		// Chromosome *chromo = new Chromosome(data);
		// solutions.push_back(Solution(chromo, i));
		solutions.push_back(Chromosome(data, i));

		// logging
		// printf("\t\t%lu ->\t%f %d ==> %d \n", solutions.size(), solutions[i].chromosome->mean,
		//		solutions[i].chromosome->clusters_count, solutions[i].index);
		// print_population();
		printf("Chromosome %d populated \n", i+1);
		printf("\n");
	}

	print_population();
}


// Utility function to print the population
void Population :: print_population() {
	printf("\nPrinting the present population ::\n");
	for (int i=0; i<solutions.size(); i++) {
		printf("Chromosome no. %d: \t\t\t Mean: %f, Clusters: %d\n", solutions[i].index, solutions[i].mean,
			solutions[i].clusters_count);

		// printf("Chromosome no. %d: \t\t\t Mean: %f, Clusters: %d\n", solutions[i].index, solutions[i].chromosome->mean,
			// solutions[i].chromosome->clusters_count);
		// print_chromosome((solutions[i].chromosome));
		// printf("\n");
	}
}


// Function which resets the indexes of all chromomes after sorting
void Population::reset_index() {
	for(int i=0; i<solutions.size(); i++) {
		solutions[i].index = i;
	}
}


// Function to carry out crossover
void Population::crossover() {
	// Pass
}