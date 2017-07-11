#ifndef __UTILS_H__
#define __UTILS_H__

#include <assert.h>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>

static std::vector<int> DEFAULT_INT_VECTOR;
static std::vector<float> DEFAULT_FLOAT_VECTOR;
static std::random_device rd;
static std::mt19937 generator(rd());

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
};

struct node {
	int l;
	int r;
	node(int l, int r)
	: l(l), r(r)
	{}
};

int uniform_int(int, int, int count=1, std::vector<int> &arr=DEFAULT_INT_VECTOR);
float uniform_float(int, int, int count=1, std::vector<float> &arr=DEFAULT_FLOAT_VECTOR);

#endif // __UTILS_H__