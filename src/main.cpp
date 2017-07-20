#include "nsga2.h"

void run(Population &);

int main(int argc, char const *argv[]) {
	std::string name;
	name = "../data/Iris.csv";
	// std::cin >> name;
	// name = "../data/"+name;
	std::cout << name << std::endl;
	Data data(name);
	Population population(data, 10);
	run(population);
	return 0;
}

void run(Population &population) {
}