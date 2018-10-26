#pragma once

#ifndef __GENOTYPE__ 
#define __GENOTYPE__

#include <vector>

#define SAFE_RELEASE(x) if(x != nullptr) { x->release(); x = nullptr; }

struct genotype
{
	std::vector<int> _data;
};

inline bool operator==(const genotype& pLhs, const genotype& pRhs) { return pLhs._data == pRhs._data; };

#endif