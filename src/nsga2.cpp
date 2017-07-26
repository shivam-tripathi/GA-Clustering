#include "nsga2.h"

NSGA2 :: NSGA2(Population *pop) {
	pop->print_population();
	this->population = pop;
	solution_count = ((this->population)->solutions).size();
	printf("NSGA2 initalised. Ready to run.\n\n\n\n\n");
}

void NSGA2::sort() {
	int k;
	printf("Sorting\n");
	for(auto elem : population->solutions) {
		elem.dominated_solutions.clear();
	}

	std::vector<Sorting> sorting;
	// Population population;

	for(int i=0; i<solution_count; i++) {
		population->solutions[i].domination_count=0;
	}

	for(int i=0; i<solution_count; i++) {
		printf("%d : \n", i);
		k=0;
		while(k<solution_count) {
			if (k == i) {
				k++;
				continue;
			}
			printf("\t%d) ", k);
			if(cmp(*(population->solutions[i].chromosome), *(population->solutions[k].chromosome))) {
				population->solutions[k].domination_count++;
				population->solutions[i].dominated_solutions.push_back(k);
				printf("Increasing... %d dominates %d \n", i, k);
			}
			k++;
		}

		printf("\n");
	}

	sorting.clear();

	for(int i=0; i<solution_count; i++) {
		printf("%d ----> %d \n", i, population->solutions[i].domination_count);
		sorting.push_back(Sorting(population->solutions[i].domination_count, i));
	}

	for (int i=0; i<sorting.size(); i++) {
		std::sort(sorting.begin()+i, sorting.end(), CmpSorting());
		int index = sorting[i].index;
		printf("%d %d\n", index, sorting[i].domination_count);
		for(auto k : population->solutions[index].dominated_solutions) {
			population->solutions[k].domination_count--;
		}
	}
}