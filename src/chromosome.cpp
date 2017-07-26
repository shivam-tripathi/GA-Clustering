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
			data->add_instances(c.mean, data->instances[c.begin]);
			nodes[c.begin].cum_sum = c.mean;
			nodes[c.begin].pos = pos++;
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
		}

		data->add_instances(c.mean, data->instances[c.end]);
		nodes[c.end].cum_sum = c.mean;
		nodes[c.end].pos = pos;

		clusters.push_back(c);
		data->avg_instance(c.mean, c.size);

		// Erase elements already used for referential integrity
		for(int j=0; j<elements.size(); j++) {
			assert(elements[j]-j < v.size());
			assert (v[elements[j]-j] == *(v.begin()+elements[j]-j));
			v.erase(v.begin() + elements[j] - j);
		}
	}
}

void Chromosome :: compute() {
	mean = 0;
	for(int i=0; i<clusters.size(); i++) {
		int j = clusters[i].begin;
		while(true) {
			float dat = data->find_distance(clusters[i].mean, data->instances[j]);
			mean += dat;
			if (j == clusters[i].end) break;
			j = nodes[j].r;
		}
	}
	printf("Mean = %f. Cluster count = %d\n", mean, clusters_count);
}

// Does Chromosome a dominates b?
bool cmp(Chromosome &a, Chromosome &b) {
	// printf("%d cmp %f ||| %d cmp %f ==> ", a.clusters_count, a.mean, b.clusters_count, b.mean);

	int ca=0, cb=0;
	// clusters_count must be as small as possible
	// Mean should be as small as possible
	if (a.clusters_count < b.clusters_count) {
		ca++;
	}
	else if (a.clusters_count > b.clusters_count) {
		cb++;
	}

	if (a.mean < b.mean) {
		ca++;
	}
	else if (a.mean > b.mean) {
		cb++;
	}

	// printf("%d %d\n", ca, cb);

	if (ca == cb) return false;
	if (ca > cb) return true;
	else return false;
}

void print_chromosome(Chromosome *chromo) {
	printf("%f %d", chromo->mean, chromo->clusters_count);
}