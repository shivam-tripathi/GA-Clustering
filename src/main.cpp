#include "data.h"

int main(int argc, char const *argv[]) {
	std::string name;
	name = "../data/Iris.csv";
	// std::cin >> name;
	// name = "../data/"+name;
	std::cout << name << std::endl;
	Data data(name);
	return 0;
}