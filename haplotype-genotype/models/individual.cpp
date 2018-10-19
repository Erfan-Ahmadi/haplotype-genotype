#include "individual.h"
#include <utility>

individual::individual(
	_In_ std::vector<haplotype*> pHaplotypes,
	_In_ std::vector<genotype*> pGenotypes)
	: _haplotypes(std::move(pHaplotypes)), _genotypes(std::move(pGenotypes))
{
}

individual::~individual()
{
	release();
}

bool individual::is_valid_for_genotype()
{
	auto _has_genotypes = std::vector<bool>(this->_genotypes.size());

	for (auto i = 0; i < this->_haplotypes.size(); i += 2)
	{
		const auto _left = this->_haplotypes[i];

		const auto _right = this->_haplotypes[i + 1];

		const auto _generated_genotype = *_left + *_right;

		if (!(*(this->_genotypes[i / 2]) == *_generated_genotype))
		{
			return false;
		}
	}

	return true;
}

std::vector<mapping> individual::get_mappings() const
{
	auto _mappings = std::vector<mapping>();

	for (auto i = 0; i < this->_haplotypes.size(); i++)
	{
		for (auto j = i + 1; j < this->_haplotypes.size(); j++)
		{
			for (auto k = 0; k < this->_genotypes.size(); k++)
			{
				if (*(this->_genotypes[k]) == *(*this->_haplotypes[i] + *this->_haplotypes[j]))
				{
					_mappings.push_back({i, j, k});
				}
			}
		}
	}

	return _mappings;
}

void individual::release()
{
	for (auto& _haplotype : this->_haplotypes)
		SAFE_RELEASE(_haplotype);
}
