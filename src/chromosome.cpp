#include "chromosome.h"

Chromosome :: Chromosome(Data &data, int index) : data(data) {
	this->index = index;
	this->mean = 0;
	this->element_count = data.count;
	this->clusters_count = uniform_int(1, 11);
	for(int i=0; i<element_count; i++) {
		nodes.push_back(node(i, i));
	}
	this->populate();
	this->compute();
}


Chromosome :: Chromosome(const Chromosome &ch) : data(ch.data) {
	index = ch.index;
	mean = ch.mean;
	element_count = ch.element_count;
	clusters_count = ch.clusters_count;
	nodes = ch.nodes;
	clusters = ch.clusters;
}

void Chromosome::operator = (const Chromosome &ch) {
	data = ch.data;
	index = ch.index;
	mean = ch.mean;
	element_count = ch.element_count;
	clusters_count = ch.clusters_count;
	nodes = ch.nodes;
	clusters = ch.clusters;
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
			data.add_instances(c.mean, data.instances[c.begin]);
			nodes[c.begin].cum_sum = c.mean;
			nodes[c.begin].pos = pos++;
		}

		for(int j=1; j<elements.size()-1; j++) {
			int index = elements[j];
			int next_index = elements[j+1];
			int prev_index = elements[j-1];

			nodes[v[index]].l = v[prev_index];
			nodes[v[index]].r = v[next_index];
			data.add_instances(c.mean, data.instances[v[index]]);
			nodes[v[index]].cum_sum = c.mean;
			nodes[v[index]].pos = pos++;
		}

		data.add_instances(c.mean, data.instances[c.end]);
		nodes[c.end].cum_sum = c.mean;
		nodes[c.end].pos = pos;

		clusters.push_back(c);
		data.avg_instance(c.mean, c.size);

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
			float dat = data.find_distance(clusters[i].mean, data.instances[j]);
			mean += dat;
			if (j == clusters[i].end) break;
			j = nodes[j].r;
		}
	}
	printf("Mean = %f. Cluster count = %d\n", mean, clusters_count);
}


Chromosome Chromosome :: crossover() {
	printf("Crossing over chromosome %d \n", index);
	print_chromosome();
	Chromosome ch(this->data, 1);

	std::vector <int> cluster_vector;
	for(int i=0; i<clusters_count; i++) {
		cluster_vector.push_back(i);
	}

	std::random_shuffle(cluster_vector.begin(), cluster_vector.end());

	for(int i=0; i+1 < cluster_vector.size(); i++) {
		// ch.cross_clusters(cluster_vector[gi], cluster_vector[i+1]);
	}

	return ch;
}

void Chromosome :: cross_clusters(int index1, int index2) {

	printf("\t\tChromsomes %d, %d will be crossed.\n", index1, index2);

	int size1 = clusters[index1].size;
	int begin_node1 = clusters[index1].begin;

	int size2 = clusters[index2].size;
	int begin_node2 = clusters[index2].begin;


	// assert(size1 < nodes.size() && size2 < nodes.size());

	int break1 = uniform_int(0, size1);
	int break2 = uniform_int(0, size2);

	printf("%d : %d || %d : %d\n", index1, size1, index2, size2);
	printf("Break point 1 is %d and break point 2 is %d\n", break1, break2);
	// return;

	int start1 = begin_node1;
	for(int i=1; i<break1; i++) {
		printf("1 %d <- %d\n", break1, i);
		if (start1 == this->nodes[start1].r) break;
		start1 = this->nodes[start1].r;
	}

	printf("1 Done.\n");

	int start2 = begin_node2;
	for(int i=1; i<break2; i++) {
		printf("2 %d <- %d\n", break2, i);
		if (start2 == this->nodes[start2].r) break;
		start2 = this->nodes[start2].r;
	}

	printf("2 Done.\n");

	this->nodes[start1].r = this->nodes[start2].r;
	this->nodes[this->nodes[start2].r].l = start1;


	this->nodes[start2].r = this->nodes[start1].r;
	this->nodes[this->nodes[start1].r].l = start2;

	printf("Done.\n");
	// compute();
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


void Chromosome :: print_chromosome() {
	printf("Chromosome: Mean - %f Cluster count - %d\n", mean, clusters_count);
	for(int i=0; i<clusters_count; i++) {
		printf("%d:\t", i);
		print_clusters(clusters[i]);
	}
}