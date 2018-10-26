#include "individual.h"
#include <utility>

individual::individual(_In_ const std::vector<genotype*>& pGenotypes) : _genotypes(pGenotypes)
{
}

individual::~individual()
{
	release();
}

void individual::set_data(
	_In_ const std::vector<haplotype*>& pHaplotypes)
{
	this->_haplotypes = pHaplotypes;
	calculate_fitness();
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

float individual::calculate_fitness()
{
	return this->_fitness 
	= (this->_haplotypes.size() + get_repeated_size()) / (this->_haplotypes.size() * 2);
}

int individual::get_repeated_size() const
{
	auto _count = 0;

	auto _counted = std::vector<bool>(this->_haplotypes.size());

	for (auto i = 0; i < this->_haplotypes.size(); i++)
	{
		if(_counted[i])
			continue;

		for (auto j = i + 1; j < this->_haplotypes.size(); j++)
		{
			if (*this->_haplotypes[i] == *this->_haplotypes[j])
			{
				_counted[j] = true;
				_count++;
			}
		}
	}

	return _count;
}

std::vector<haplotype*> individual::get_hapolotypes_without_repetition() const
{
	auto _ret = std::vector<haplotype*>();

	for (const auto& _haplotype : this->_haplotypes)
	{
		auto _has_haplotype = false;
		for (const auto& _r : _ret)
		{
			//TODO: pointer equal
			if (*_r == *_haplotype)
			{
				_has_haplotype = true;
				break;
			}
		}

		if (!_has_haplotype)
			_ret.push_back(_haplotype);
	}

	return _ret;
}

float individual::get_fitness() const
{
	return this->_fitness;
}

void individual::release()
{
	//for (auto& _haplotype : this->_haplotypes)
	//	SAFE_RELEASE(_haplotype);
}
