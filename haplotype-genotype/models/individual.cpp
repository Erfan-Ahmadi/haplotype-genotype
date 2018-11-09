#include "individual.h"
#include <utility>

individual::individual(): _fitness(0)
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

void individual::set_data_at(const int& i, haplotype* pHaplotype)
{
	release_haplotype(_haplotypes[i]);
	_haplotypes[i] = pHaplotype;
}

float individual::calculate_fitness()
{
	return this->_fitness = get_repeated_size();
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

void individual::release_haplotype(haplotype*& pHaplotype)
{
	pHaplotype->_data.clear();
	pHaplotype->_data.shrink_to_fit();
	delete pHaplotype;
	pHaplotype = nullptr;
}

void individual::release()
{
	for (auto& _haplotype : this->_haplotypes)
	{
		release_haplotype(_haplotype);
	}

	this->_haplotypes.clear();
	this->_haplotypes.shrink_to_fit();
}
