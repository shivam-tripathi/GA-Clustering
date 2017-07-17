#include "data.h"

Data :: Data (std::string s) : LoadData(s) {}

instance Data :: get_mean(std::vector<int> &indices, std::vector<int> &referential_indices) {
	instance mean(0,0,0,0,0);
	for(int i=0; i<referential_indices.size(); i++) {
		int index = referential_indices[i];
		int actual_index = indices[index];
		add_instances(mean, instances[actual_index]);
	}
	avg_instance(mean, referential_indices.size());
	return mean;
}

void Data :: add_instances(instance &mean, const instance &ins) {
	mean.slength += ins.slength;
	mean.swidth += ins.swidth;
	mean.plength += ins.plength;
	mean.pwidth += ins.pwidth;
	mean.type += ins.type;
}

float Data :: add_instance(const instance &instance) {
	return (instance.slength + instance.swidth + instance.plength + instance.pwidth);
}

void Data :: avg_instance(instance &mean, int size) {
	mean.slength /= ((float)size);
	mean.swidth /= ((float)size);
	mean.plength /= ((float)size);
	mean.pwidth /=((float)size);
	mean.type /= ((int)size);
}

float Data :: find_distance(instance &a, instance &b) {
	float ans = 0;
	ans += (a.slength - b.slength) * (a.slength - b.slength);
	ans += (a.swidth - b.swidth) * (a.swidth - b.swidth);
	ans += (a.plength - b.plength) * (a.plength - b.plength);
	ans += (a.pwidth - b.pwidth) * (a.pwidth - b.pwidth);
	ans += (a.type - b.type) * (a.type - b.type);
	return ans;
}