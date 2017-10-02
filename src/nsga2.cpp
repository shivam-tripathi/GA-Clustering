#include "nsga2.h"


// NSGA2 constructor: Simply creates an instance of NSGA2 solution
// Initialised using passed Population instance pointer
NSGA2 :: NSGA2(Population &population) : population(population) {
	printf("Inistialising NSGA2 object ...\n");

	// Number of chromosomes
	solution_count = population.solutions.size();

	for(int i=0; i<solution_count; i++) {
		sorting.push_back(Sorting(i, 0, 0));
	}

	printf("\nNSGA2 initalised with solution count = %d. Ready to run.\n\n", solution_count);

	// Pretty printing
	for(int i=0; i<100; i++) printf("*");
	printf("\n");
}


// Base function - sorts the population
void NSGA2 :: sort() {
	printf("Beginning sorting ...\n");
	for(int i=0; i<50; i++) printf("-");
	printf("\n");

	// Reset sorting vector
	reset();

	// Set domination values for the solutions
	set_domination();
	printf("\nDomination set.\n");
	for(int i=0; i<50; i++) printf("-");
	printf("\n");

	// Set distance values for the solutions
	set_distance();
	printf("\nDistance set.\n");
	for(int i=0; i<50; i++) printf("-");
	printf("\n");

	// Only for logging purposes, this is a redundant step as it is carried out in the while loop below
	std::sort(sorting.begin(), sorting.end(), CmpSorting());
	// Log: Order of solutions
	printf("\nOrder of solutions:\n");
	for(int i=0; i<solution_count; i++) printf("\t%d :: %d, %f\n",
		sorting[i].index, sorting[i].domination_count, sorting[i].distance);

	// Maps index of chromosome indexes with present sorted index
	// For example, if initially chromosome at index 6 after sorting is supposed to be at index 1,
	// it stores map[6] = 1
	int map[solution_count];

	int begin = 0, end = 0;
	while(begin < solution_count && end < solution_count) {

		std::sort(sorting.begin()+begin, sorting.end(), CmpSorting());
		for(int i=begin; i<solution_count; i++) {
			map[sorting[i].index] = i;
		}

		// Traverse to the index till the denomination count is same (supposedly 0)
		int check = sorting[begin].domination_count;
		while(end<solution_count && sorting[end].domination_count == check) end++;
		// printf("BEGIN %d END %d\n", begin, end-1);

		// Reduce the denomination count of all solutions which are dominated solutions till the index `end`
		for(int i=begin; i<end; i++) {
			for(int j=0; j<sorting[i].domination_set.size(); j++) {
				int original_index = sorting[i].domination_set[j];
				int mapped_index = map[original_index];
				sorting[mapped_index].domination_count--;
			}
		}
		begin = end;
 	}

 	// Inplace swap of population according to sorting vector indices
 	// First map all indexed chromosomes against their initial positions (which is same)
 	for(int i=0; i<solution_count; i++) map[i] = i;

 	for(int i=0; i<solution_count; i++) {

 		// sorting_index is the index of chromosome which should be present at position i
 		int sorting_index = sorting[i].index;
 		// original_index is the location of the chromosome indexed as sorting_index
 		int original_index = map[sorting_index];
 		// present_index is the index of the chromosome presently at position i
 		int present_index = population.solutions[i].index;

		// Logic is to simply swap the chromosome indexed sorting_index to position i repeatedly
		// First we ascertain where the chromosome with index sorting_index is present, we store this in original_index
		// We do this using the mapping of index against their present location (initially index i is at position i)
		// Then we ascertain which indexed chromosome is present at position i
		// Finally we swap the chromosomes at location original_index and i
		// We update mappings as follows:
		// 		1. The position of chromosome indexed sorting_index is now i
		// 		2. The position of chromosome indexed present_index is now original_index

 		// swap position i with sorting_index
 		std::swap(population.solutions[original_index], population.solutions[i]);
 		map[sorting_index] = i;
 		map[present_index] = original_index;
 	}

 	// Logging: Final positions after inplace sorting
 	printf("\nFinal positions of chromosomes in the positions after inplace sort: \n");
 	for(int i=0; i<solution_count; i++) printf("\t%d) Chromosome %d\n", i, population.solutions[i].index);

 	printf("\nSetting new indexes ...\n");
 	set();

 	printf("\nInplace sorting done.\n");
 	for(int i=0; i<100; i++) printf("*");
 	printf("\n");
}


void NSGA2 :: reset() {
	for(int i=0; i<sorting.size(); i++) {
		sorting[i].index = i;
		sorting[i].domination_count = sorting[i].distance = 0;
		sorting[i].domination_set.clear();
	}
}


void NSGA2 :: set() {
	for(int i=0; i<population.solutions.size(); i++) {
		population.solutions[i].index = i;
	}
}


void NSGA2 :: set_domination() {

	for(int i=0; i<solution_count; i++) {
		printf("Setting domination count for chromosome index ... %d\n", population.solutions[i].index);
		for(int j=0; j<solution_count; j++) {
			if (i == j) {
				continue;
			}

			// printf("\t\tChecking against %d :: ", population.solutions[j].index);

			if(cmp(population.solutions[i], population.solutions[j])) {
				sorting[j].domination_count++;
				sorting[i].domination_set.push_back(j);
				printf("\t%d dominates %d \n", i, j);
			}
			// printf("\n");
		}
	}
}


void NSGA2::set_distance() {

	// Vectors to hold value of objective functions in sorted order
	std::vector<Objective> ob1;
	std::vector<Objective> ob2;

	for(int i=0; i<solution_count; i++) {
		ob1.push_back(Objective(i, population.solutions[i].clusters_count));
		ob2.push_back(Objective(i, population.solutions[i].mean));
	}

	std::sort(ob1.begin(), ob1.end(), CmpObjective());
	std::sort(ob2.begin(), ob2.end(), CmpObjective());

	// Logging: Chromosomes in order of their objective function values
	printf("\nclusters_count ranking :\n");
	for(int i=0; i<solution_count; i++) printf("\t%d :: %f\n", ob1[i].index, ob1[i].value);
	printf("\nmean ranking :\n");
	for(int i=0; i<solution_count; i++) printf("\t%d :: %f\n", ob2[i].index, ob2[i].value);

	// Range of first and second objective function
	float range1 = ob1[0].value - ob1[solution_count-1].value;
	float range2 = ob2[0].value - ob2[solution_count-1].value;

	// Loop over all positions of objective functions to get the distance of each solution
	for(int i=0; i<solution_count; i++) {
		int index1 = ob1[i].index;
		int index2 = ob2[i].index;

		// Set the distance of solution on the edges to be infinity (according to NSGA2)
		if (i==0 || i==solution_count-1) {
			sorting[index1].distance += inf;
			sorting[index2].distance += inf;
			continue;
		}

		sorting[index1].distance += (ob1[i-1].value - ob1[i+1].value)/range1;
		sorting[index2].distance += (ob2[i-1].value - ob2[i+1].value)/range2;
	}

	// Logging: Print all distances
	printf("\nFinal distances of the solution set ::\n");
	for(int i=0; i<solution_count; i++) printf("\t%d :: %f\n", sorting[i].index, sorting[i].distance);
}
