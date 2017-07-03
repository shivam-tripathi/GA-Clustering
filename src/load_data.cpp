#include "load_data.h"

LoadData :: LoadData(std::string s) {
	this->name_csv = s;
	load_data();
	std::cout << "Read " << count << " records from " << name_csv << " file." << std::endl;
}

void LoadData :: load_data() {
	int id;
	float a, b, c, d;
	char *str = new char[100];
	size_t size = 100;

	if(std::FILE *f = std::fopen(name_csv.c_str(), "r")) {
		std::cout << "Beginning " << std::endl;
		getline(&str, &size, f);
		while(std::fscanf(f, "%d,%f,%f,%f,%f,%s", &id, &a, &b, &c, &d, str) == 6) {
			std::string s(str);
			int type = switch_type(s);
			// Logging message to be inserted here, separate log file stream instead of present stdout to be used
			// fprintf(stdout, "%d, %f, %f, %f, %f, %d\n", id, a, b, c, d, type);
			instance new_intance(a, b, c, d, type);
			instances.push_back(new_intance);
			count += 1;
		}
	}
	else {
		std::cout << "Error opening file" << std::endl;
	}

	delete[] str;
}


int LoadData :: switch_type(std::string s) {
	if(s == "Iris-setosa") return 1;
	if(s == "Iris-versicolor") return 2;
	if(s == "Iris-virginica") return 3;
	return 4;
}
