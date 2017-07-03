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