#pragma once

#ifndef __INDIVIDUAL__ 
#define __INDIVIDUAL__

#include "genotype.h"
#include "haplotype.h"

class individual
{
public:
	explicit individual(_In_ const std::vector<haplotype>& pData);

	individual(
		_In_ const haplotype* pData,
		_In_ const int& pSize);

	~individual();

	bool is_valid_for_genotype(_In_ const genotype* pGenotypes, _In_ const int& pSize)
	{
		auto _has_genotypes = std::vector<bool>(pSize);

		for(auto i = 0; i < this->_haplotypes.size(); i++)
		{
			const auto _left = this->_haplotypes[i];

			for(auto j = i + 1; j < this->_haplotypes.size(); j++)
			{
				const auto _right = this->_haplotypes[j];

				const auto _generated_genotype = _left + _right;

				for(auto k = 0; k < pSize; k++)
				{
					if(*(pGenotypes + i) == *_generated_genotype)
					{
						_has_genotypes[i] = true;
					}
				}

				auto _generates_all = true;

				for (const auto& _gen : _has_genotypes)
				{
					if (!_gen)
						_generates_all = false;
				}

				if (_generates_all)
					return true;
			}
		}

		return false;
	}

#pragma region Setters
#pragma endregion 

#pragma region Getters
	float get_fitness() const;
#pragma endregion 

	void release();

private:
	std::vector<haplotype> _haplotypes;
};

#endif
