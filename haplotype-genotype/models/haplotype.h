#pragma once

#ifndef __HAPLOTYPE__ 
#define __HAPLOTYPE__

#include <vector>
#include "genotype.h"

class haplotype
{
public:
	haplotype(_In_ const std::vector<int>& pData);

	haplotype(
		_In_ const int* pData,
		_In_ const int& pSize);

	~haplotype();

	genotype* operator+(const haplotype& pSecond) const;

	genotype* get_merge_genotyped(const haplotype& pSecond) const;

#pragma region Setters
#pragma endregion 

#pragma region Getters
	const std::vector<int>& get_data() const;
#pragma endregion 

	void release();

private:
	std::vector<int> _data;
};

#endif
