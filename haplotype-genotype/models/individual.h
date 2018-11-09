/*
Source			 : Please direct any bugs to https://github.com/Erfan-Ahmadi/haplotype-genotype issues
Developers		 : Erfan Ahmadi
*/

#pragma once

#ifndef __INDIVIDUAL__ 
#define __INDIVIDUAL__

#include "genotype.h"
#include "haplotype.h"

class individual
{
public:
	individual();
	individual(const individual& pIndividual) = delete;
	~individual();

	//bool is_valid_for_genotype();

	float calculate_fitness();

	int get_repeated_size() const;

	std::vector<haplotype*> get_hapolotypes_without_repetition() const;

	individual* copy() const
	{
		auto _elite = new individual();
		auto _hap_data = std::vector<haplotype*>(this->_haplotypes.size());

		for (auto i = 0; i < _hap_data.size(); i++)
			_hap_data[i] = new haplotype(*this->get_data_at(i));

		_elite->set_data(_hap_data);

		return _elite;
	}

#pragma region Setters
	void set_data(
		_In_ const std::vector<haplotype*>& pHaplotypes);

	void set_data_at(const int& i, haplotype* pHaplotype);
#pragma endregion 

#pragma region Getters

	float get_fitness() const;

	void release_haplotype(std::vector<haplotype*>::value_type& pHaplotype);

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
};

#endif
