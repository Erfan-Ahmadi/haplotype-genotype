#pragma once

#ifndef __HAPLOTYPE__ 
#define __HAPLOTYPE__

#include <vector>
#include "genotype.h"

struct haplotype
{
	std::vector<bool> _data;
};

inline bool operator==(const haplotype& pLhs, const haplotype& pRhs)
{
	return pLhs._data == pRhs._data;
}

inline genotype* operator+(const haplotype& pLhs, const haplotype& pRhs)
{
	if (pLhs._data.size() != pRhs._data.size())
		return nullptr;

	auto _genotype_data = std::vector<char>(pLhs._data.size());

	for (auto i = 0; i < pLhs._data.size(); i++)
	{
		if (pLhs._data[i] == 1 && pRhs._data[i] == 1)
			_genotype_data[i] = 1;
		else if (pLhs._data[i] == 0 && pRhs._data[i] == 0)
			_genotype_data[i] = 0;
		else
			_genotype_data[i] = 2;
	}

	return new genotype{ _genotype_data };
}

#endif
