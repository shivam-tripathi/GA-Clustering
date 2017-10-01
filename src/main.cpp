#include "nsga2.h"

void run(Population *);

int main(int argc, char const *argv[]) {
	std::string name;
	int count_chromosomes;
	// Take input in name to execute different data file, number of chromosomes
	// load_data is presently configured to work with Iris data set
	// Changing input files will require necessary changes in the load_data file structure and a couple of utility files
	name = "../data/Iris.csv";
	count_chromosomes = 10;

	// Pretty printing
	for(int i=0; i<50; i++) printf("*");
	std::cout << "\n\nFile input: " << name << std::endl;
	std::cout << "Number of chromosomes: " << count_chromosomes << "\n" << std::endl;
	for(int i=0; i<50; i++) printf("*");
	printf("\n");


	Data data(name);
	// Population *population = new Population(data, count_chromosomes);
	Population population(data, count_chromosomes);

	// Write tests to verify if all data has loaded successfully
	printf("\nPopulation initialised successfully.\n");

	// Beginning execution
	printf("\n");
	for(int i=0; i<50; i++) printf("*");

 	printf("\n\nBeginning execution ... ");

 	NSGA2 solve(population);
 	solve.sort();
	return 0;
}