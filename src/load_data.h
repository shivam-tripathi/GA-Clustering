#ifndef __LOAD_DATA_H__
#define __LOAD_DATA_H__

#include "utils.h"

class LoadData {
public:
	int count;
	std::string name_csv;
	std::vector<instance> instances;

	LoadData(std::string);
	int switch_type(std::string);
	void load_data();
};

#endif // __LOAD_DATA_H__