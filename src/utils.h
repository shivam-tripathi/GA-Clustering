#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <string>
#include <vector>

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

struct node {
	int l;
	int r;
};

#endif // __UTILS_H__