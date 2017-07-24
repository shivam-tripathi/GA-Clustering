#ifndef __UTILS_H__
#define __UTILS_H__

#include <assert.h>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>

static std::vector<int> DEFAULT_INT_VECTOR;
static std::vector<float> DEFAULT_FLOAT_VECTOR;
static std::random_device rd;

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
void print_instances(instance &);

#endif // __UTILS_H__