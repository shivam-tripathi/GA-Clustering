#include "nsga2.h"

NSGA2 :: NSGA2(Population *pop) {
	printf("Inistialising NSGA2 object ...\n");
	pop->print_population();
	this->population = pop;
	solution_count = ((this->population)->solutions).size();
	printf("NSGA2 initalised with solution count = %d. Ready to run.\n\n\n\n\n", solution_count);
}

void NSGA2::sort(int erase) {

	printf("Sorting ... \n");

	set_distance();
	printf("Distance set.\n");
	set_domination_count();
	printf("Domination count set.\n");

	std::vector<Sorting> sorting;
	sorting.clear();

	for(int i=0; i<solution_count; i++) {
		printf("%d ----> %d and %f \n", i, population->solutions[i].domination_count, population->solutions[i].distance);
		sorting.push_back(Sorting(i, population->solutions[i].domination_count, population->solutions[i].distance));
	}

	for (int i=0; i<sorting.size(); i++) {
		std::sort(sorting.begin()+i, sorting.end(), CmpSorting());
		int index = sorting[i].index;
		printf("%d %d\n", index, sorting[i].domination_count);
		for(auto k : population->solutions[index].dominated_solutions) {
			population->solutions[k].domination_count--;
		}
	}

	std::vector<Sorting> erase_indices(sorting.end()-erase, sorting.end());
	std::sort(erase_indices.begin(), erase_indices.end(), CmpErase());
	for(int i=0; i<erase; i++) {
		population->solutions.erase(population->solutions.begin() + erase_indices[i].index-i);
	}

	for(auto elem : population->solutions) {
		printf(">> %d elem\n", elem.index);
	}
	population->reset_index();
}


void NSGA2::set_domination_count() {

	for(int i=0; i<solution_count; i++) {
		population->solutions[i].domination_count=0;
		population->solutions[i].dominated_solutions.clear();
	}

	int k;
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
				printf("Increasing : %d dominates %d \n", i, k);
			}
			k++;
		}
		printf("\n");
	}
}

void NSGA2::set_distance() {

	for(int i=0; i<solution_count; i++) {
		population->solutions[i].distance=0;
	}

	std::vector<Objective> first, second;
	for(int i=0; i<solution_count; i++) {
		first.push_back(Objective(i, population->solutions[i].chromosome->clusters_count));
		second.push_back(Objective(i, population->solutions[i].chromosome->mean));
	}

	std::sort(first.begin(), first.end(), CmpObjective());
	std::sort(second.begin(), second.end(), CmpObjective());

	// for(auto k : first) printf("Sorted comparators :: %f %d\n", k.value, k.index);
	for(int i=0; i<first.size(); i++) {
		printf("%d :: %f %d\n", i, first[i].value, first[i].index);
	}

	float divfirst = first[first.size()-1].value - first[0].value;
	float divsecond = second[second.size()-1].value - second[0].value;
	population->solutions[first[first.size()-1].index].distance = INT_MAX;
	population->solutions[first[0].index].distance = INT_MAX;
	population->solutions[second[second.size()-1].index].distance = INT_MAX;
	population->solutions[second[0].index].distance = INT_MAX;

	for(int i=1; i<first.size()-1; i++) {
		printf("Setting value %d and %d\n", first[i].index, second[i].index);
		if (population->solutions[first[i].index].distance != INT_MAX) {
			population->solutions[first[i].index].distance += ((first[i+1].value - first[i-1].value) / divfirst);
		}
		if (population->solutions[second[i].index].distance != INT_MAX) {
			population->solutions[second[i].index].distance += ((second[i+1].value - second[i-1].value) / divsecond);
		}
	}
}