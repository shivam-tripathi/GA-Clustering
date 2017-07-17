#ifndef __DATA_H__
#define __DATA_H__

#include "load_data.h"

class Data : public LoadData {
public:
	Data(std::string s);
	instance get_mean(std::vector<int> &, std::vector<int> &);

	void add_instances(instance &, const instance &);
	float add_instance(const instance &);
	void avg_instance(instance &, int);
	float find_distance(instance &, instance &);
};

#endif // __DATA_H__