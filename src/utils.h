#ifndef __UTILS_H__
#define __UTILS_H__

#include <assert.h>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>


// Utility values and dummy vectors for aiding default arguments for some functions
// An implementation detail only
const int inf = (int)1e9+100;
static std::vector<int> DEFAULT_INT_VECTOR;
static std::vector<float> DEFAULT_FLOAT_VECTOR;
static std::random_device rd;


// This stores the value of an instance :: specifically value of each property
// This is structure which represents how the entire data is loaded into the system (i.e. in form of instances)
struct instance {
	float slength;
	float swidth;
	float plength;
	float pwidth;
	int type;
	instance(float a, float b, float c, float d, int e)
	: slength(a), swidth(b), plength(c), pwidth(d), type(e)
	{}
};


// This structure the details of every cluster in the entire data set
// The typical properties of each cluster are:
//		1. Index of beginning node of the cluster
//		2. Index of last node of the cluster
//		3. The size of the cluster
//		4. Instance which stores the mean of the cluster
// The mean instance is important as it serves an integral role in determining the value of
// the objective function : Minimise sum of average distances of cluster elements to cluster centre
// The mean instance serves as the cluster center
struct cluster {
	int begin;
	int size;
	int end;
	instance mean;
	cluster()
	: mean(instance(0,0,0,0,0))
	{}
};

struct node {
	int l;
	int r;
	int pos;
	instance cum_sum;
	node(int l, int r)
	: l(l), r(r), pos(-1), cum_sum(instance(0,0,0,0,0))
	{}
};

int uniform_int(int, int, int count=1, std::vector<int> &arr=DEFAULT_INT_VECTOR);
float uniform_float(int, int, int count=1, std::vector<float> &arr=DEFAULT_FLOAT_VECTOR);
float normal_float(int, int, int count=1, std::vector<float> &arr=DEFAULT_FLOAT_VECTOR);
void print_instances(instance &);
void print_clusters(cluster &);

#endif // __UTILS_H__