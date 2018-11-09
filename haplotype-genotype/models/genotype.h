/*
Source			 : Please direct any bugs to https://github.com/Erfan-Ahmadi/haplotype-genotype issues
Developers		 : Erfan Ahmadi
*/

#pragma once

#ifndef __GENOTYPE__ 
#define __GENOTYPE__

#include <vector>

#define SAFE_RELEASE(x) if(x != nullptr) { x->release(); x = nullptr; }

struct genotype
{
	std::vector<char> _data;
};

inline bool operator==(const genotype& pLhs, const genotype& pRhs) { return pLhs._data == pRhs._data; };

#endif