#include "utils.h"

// Utility function for generating uniform random number between l, r
// If number of random digits required is 1, it simply returns the digit
// Otherwise it will fill the passed vector reference and return size of final vector
int uniform_int(int l, int r, int count, std::vector<int> &arr) {
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(l, r);
	auto dice = std::bind (distribution, generator);
	if (count == 1) {
		return dice();
	}

	std::set<int> s;
	for(int i=0; i<count;) {
		int t = dice();
		if (s.find(t) != s.end()) {
			continue;
		}
		s.insert(t);
		i++;
		arr.push_back(t);
	}
	return arr.size();
}


// Similar function as for uniform_int, but for float
float uniform_float(int l, int r, int count, std::vector<float> &arr) {
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(l, r);
	auto dice = std::bind(distribution, generator);
	if (count == 1) {
		return dice();
	}

	for(int i=0; i<count; i++) {
		arr.push_back(dice());
	}
	return 0;
}


// Utility function to print each instance for data loaded
// Presently it is configured for Iris data set
void print_instance(instance &ins) {
	printf("%f %f %f %f %d\n", ins.slength, ins.swidth, ins.plength, ins.pwidth, ins.type);
}