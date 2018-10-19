#pragma once

#ifndef __INDIVIDUAL__ 
#define __INDIVIDUAL__

#include "genotype.h"
#include "haplotype.h"

struct mapping
{
	int _h1_index;
	int _h2_index;
	int _gt_index;
};

class individual
{
public:
	explicit individual(
		_In_ std::vector<haplotype*> pHaplotypes,
		_In_ std::vector<genotype*> pGenotypes);
	~individual();

	bool is_valid_for_genotype();

	std::vector<mapping> get_mappings() const;

#pragma region Setters
#pragma endregion 

#pragma region Getters

	float get_fitness() const
	{
		return get_mappings().size();
	}

#pragma endregion 

	void release();

private:
	std::vector<haplotype*> _haplotypes;
	std::vector<genotype*> _genotypes;
};

#endif
