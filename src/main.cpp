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
	for(int i=0; i<100; i++) printf("*");
	std::cout << "\n\nFile input: " << name << std::endl;
	std::cout << "Number of chromosomes: " << count_chromosomes << "\n" << std::endl;
	for(int i=0; i<100; i++) printf("*");
	printf("\n");


	Data data(name);
	Population population(data, count_chromosomes);

	// Write tests to verify if all data has loaded successfully
	printf("\nPopulation initialised successfully.\n");

	// Beginning execution
	printf("\n");
	for(int i=0; i<100; i++) printf("*");

 	printf("\n\nBeginning execution ... ");

 	NSGA2 solve(population);

	// Run the GA for 100 turns
	int epoch = 100, mutation_const = uniform_int(1, 100);
	while(epoch--) {
		// Pretty printing
		for(int i=0; i<100; i++) printf("#");
		printf("\n\t\t\t\t\t\t\t\t\t\t\tEpoch %d\n", epoch+1);
		for(int i=0; i<100; i++) printf("#");
		printf("\n");

		// First sort the population
		solve.sort();

		// Carry out crossover
		// During the beginning epochs greater lesser number of elites are withheld
		// Later, we keep greater number of elite back
		// Elites withheld are never more than 5
		int elite_withheld = std::min(5, 10-epoch/10);
		population.crossover(elite_withheld);

		if (uniform_int(1, 100) == mutation_const) {
			population.mutation();
		}
	}
	return 0;
}