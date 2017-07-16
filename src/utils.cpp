#include "utils.h"

int uniform_int(int l, int r, int count, std::vector<int> &arr) {
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
	return 0;
}

float uniform_float(int l, int r, int count, std::vector<float> &arr) {
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