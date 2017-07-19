#include "chromosome.h"

Chromosome :: Chromosome(Data &_data) {
	this->mean = 0;
	this->data = &(_data);
	this->element_count = data->count;
	this->clusters_count = uniform_int(1, 11);
	for(int i=0; i<element_count; i++) {
		nodes.push_back(node(i, i));
	}
	this->populate();
	this->compute();
}

void Chromosome :: populate() {
	std::vector<int> v;
	float sum;
	for(int i=0; i<element_count; i++) {
		v.push_back(i);
	}

	// std::vector<int> check;
	int cluster_size = element_count/clusters_count;

	int size = element_count;
	for (int i=1; i<=clusters_count; i++) {

		cluster c;
		c.size = uniform_int(std::max(1, cluster_size-10), cluster_size);

		std::vector<int> elements;
		if (i < clusters_count) {
			uniform_int(0, v.size()-1, c.size, elements);
			sort(elements.begin(), elements.end());
		}
		else {
			c.size = v.size();
			if (c.size > cluster_size+10) {
				clusters_count++;
				i--;
				continue;
			}
			for(int i=0; i<v.size(); i++) {
				elements.push_back(i);
			}
		}


		c.begin = v[elements[0]];
		c.end = v[elements[elements.size()-1]];

		int pos = 1;
		if (elements.size() > 1) {
			nodes[c.begin].r = v[elements[1]];
			// printf("\t\t\t\tClusters no. %d ===> %d\n", i, c.begin);
			data->add_instances(c.mean, data->instances[c.begin]);
			nodes[c.begin].cum_sum = c.mean;
			nodes[c.begin].pos = pos++;
			// check.push_back(v[elements[0]]);
			// check.push_back(v[elements[elements.size()-1]]);
		}

		for(int j=1; j<elements.size()-1; j++) {
			int index = elements[j];
			int next_index = elements[j+1];
			int prev_index = elements[j-1];

			nodes[v[index]].l = v[prev_index];
			nodes[v[index]].r = v[next_index];
			data->add_instances(c.mean, data->instances[v[index]]);
			nodes[v[index]].cum_sum = c.mean;
			nodes[v[index]].pos = pos++;
			// printf("\t\t\t\tClusters no. %d ===> %d\n", i, v[index]);
			// check.push_back(v[elements[i]]);
		}

		data->add_instances(c.mean, data->instances[c.end]);
		nodes[c.end].cum_sum = c.mean;
		nodes[c.end].pos = pos;
		// printf("\t\t\t\tClusters no. %d ===> %d\n\n\n", i, v[c.end]);

		clusters.push_back(c);
		data->avg_instance(c.mean, c.size);
		// sort(check.begin(), check.end());

		// Erase elements already used for referential integrity
		for(int j=0; j<elements.size(); j++) {
			assert(elements[j]-j < v.size());
			assert (v[elements[j]-j] == *(v.begin()+elements[j]-j));
			v.erase(v.begin() + elements[j] - j);
		}
	}
	// for(auto k: check) printf("\t\t%d\n", k);
	// printf("\n\n");
}

void Chromosome :: compute() {
	mean = 0;
	// printf("Total clusters %lu <==> %d \n", clusters.size(), clusters_count);
	// std::vector<int> v;
	for(int i=0; i<clusters.size(); i++) {
		int j = clusters[i].begin;
		// printf("\n Cluster size %d <==> %d\n", clusters[i].size, nodes[clusters[i].end].pos);
		while(true) {
			// printf("%d ", j);
			// v.push_back(j);
			// mean += data->find_distance(clusters[i].mean, data->instances[i]);
			if (j == clusters[i].end) break;
			j = nodes[j].r;
		}
	}
	// sort(v.begin(), v.end());
	// for(auto k : v) std::cout << k << std::endl;
}


bool cmp(Chromosome &a, Chromosome &b) {
	int ca=0, cb=0;
	// clusters_count must be as small as possible
	// Mean should be as small as possible
	if (a.clusters_count > b.clusters_count) {
		ca++;
	}
	else if (a.clusters_count < b.clusters_count) {
		cb++;
	}

	if (a.mean > b.mean) {
		cb++;
	}
	else if (a.mean < b.mean) {
		ca++;
	}

	if (ca == cb) return false;
	if (ca > cb) return true;
	else return false;
}

