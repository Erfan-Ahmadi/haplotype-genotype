#pragma once

#ifndef __INDIVIDUAL__ 
#define __INDIVIDUAL__

#include "genotype.h"
#include "haplotype.h"

struct resolution
{
	haplotype* _h1;
	haplotype* _h2;
};

class individual
{
public:
	explicit individual(_In_ const std::vector<genotype*>& pGenotypes);

	~individual();

	bool is_valid_for_genotype();

	float calculate_fitness();

	int get_repeated_size() const;

	std::vector<haplotype*> get_hapolotypes_without_repetition() const;

#pragma region Setters
	void set_data(
		_In_ const std::vector<haplotype*>& pHaplotypes);

	void set_data_at(const int& i, haplotype* pHaplotype)
	{
		 _haplotypes[i] = pHaplotype;
	}
#pragma endregion 

#pragma region Getters
	float get_fitness() const;

	const std::vector<haplotype*>* get_data() const
	{
		return &_haplotypes;
	}

	haplotype* get_data_at(const int& i) const
	{
		return _haplotypes[i];
	}
#pragma endregion 

	void release();

private:
	float _fitness;
	std::vector<haplotype*> _haplotypes;
	std::vector<genotype*> _genotypes;
};

#endif
