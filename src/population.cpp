#include "population.h"


Population :: Population(Data &data, int n) {
	// Initialise population's data, clean solutions vector (incase already filled)
	// this->data = &(data);
	solutions.clear();

	// Add chromosomes to the solutions vector
	// n is the number of chromosomes, sent as arguments from the main function
	printf("\nAdding chromosomes to the population ...\n\n");
	for(int i=0; i<n; i++) {
		solutions.push_back(Chromosome(data, i));

		// Log: Chromosome indexed i set successfully
		printf("Chromosome %d populated \n\n", i+1);
	}

	print_population();
}


// Utility function to print the population
void Population :: print_population() {
	printf("\nPrinting the present population ::\n");
	for (int i=0; i<solutions.size(); i++) {
		printf("Chromosome no. %d: \t\t\t Mean: %f, Clusters: %d\n", solutions[i].index, solutions[i].mean,
			solutions[i].clusters_count);
	}
}


// Function which resets the indexes of all chromomes after sorting
void Population :: reset_index() {
	for(int i=0; i<solutions.size(); i++) {
		solutions[i].index = i;
	}
}


// Function to carry out crossover
void Population :: crossover(int elite_withheld) {

	// Generate parent chromosome index using normal distribution
	// The most fit chromosome is at the mean region, and least fit chromosome at boundary
	// Method: We generate random numbers of count (total chromosomes - number of elites held back)
	// The random numbers are generated with mean = 10*number of chromosomes, with SD = 10*number of chromosomes
	// Rest is self explanatory.
	std::vector<float> cross_over;
	cross_over.clear();
	normal_float(0, 10*solutions.size(), (solutions.size()-elite_withheld), cross_over);

	for (int i = 0; i < cross_over.size(); ++i) {
		if (cross_over[i] < 0) cross_over[i] *= -1;
		cross_over[i] = (int)cross_over[i] / 10;
	}

	for(int i=0; i<cross_over.size(); i++) {
		printf("%lu >> %f | \n", solutions.size(), cross_over[i]);
	}
	printf("\n");

	// Generate the next offspring
	std::vector<Chromosome> offsprings;
	for(int i=0; i<cross_over.size(); i++) {
		int parent_number = cross_over[i];
		offsprings.push_back(solutions[parent_number].crossover());
	}

	// Overwrite the lesser fit offsprings
	int index = solutions.size()-1;
	for(int j=0; j<offsprings.size(); j++) {
		solutions[index--] = offsprings[j];
	}

	reset_index();
}


// Function to carry out mutation
void Population :: mutation() {
	// Pass for now
}