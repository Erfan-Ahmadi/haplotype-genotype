#include "genetic_algorithm.h"
#include <stdlib.h>
#include <time.h>   
#include <iostream>

void genetic_algorithm::run(
	_In_ std::vector<genotype*> pGenotypes,
	_In_ const int& pPopulationSize)
{
	srand(time(0));

	std::vector<individual*> _population;

	for (int i = 0; i < pPopulationSize; i++)
	{
		auto _haplotypes = std::vector<haplotype*>();

		for (const auto& _genotype : pGenotypes)
		{
			const auto _generating_haplotypes = _get_generating_haplotypes(_genotype);
			_haplotypes.insert(_haplotypes.end(), _generating_haplotypes.begin(), _generating_haplotypes.end());
		}

		auto _individual = new individual(_haplotypes, pGenotypes);
		_population.push_back(_individual);
		std::cout << _individual->get_fitness() << std::endl;
	}

	release_population(_population);
}

const individual* genetic_algorithm::get_population_fittest(_In_ const std::vector<individual*>& pPopulation)
{
	auto _fittest = pPopulation[0];

	for (auto i = 1; i < pPopulation.size(); i++)
	{
		if (pPopulation[i]->get_fitness() > _fittest->get_fitness())
		{
			_fittest = pPopulation[i];
		}
	}

	return _fittest;
}

void genetic_algorithm::release_population(_In_ std::vector<individual*>& pPopulation)
{
	for (auto& _individual : pPopulation)
		SAFE_RELEASE(_individual);
	pPopulation.clear();
}

std::vector<haplotype*> genetic_algorithm::_get_generating_haplotypes(genotype* pGenotype)
{
	auto _data1 = std::vector<int>(pGenotype->get_data().size());
	auto _data2 = std::vector<int>(pGenotype->get_data().size());

	for (auto i = 0; i < pGenotype->get_data().size(); i++)
	{
		const auto _g = pGenotype->get_data()[i];

		if (_g == 0)
			_data1[i] = _data2[i] = 0;
		else if (_g == 1)
			_data1[i] = _data2[i] = 1;
		else if (_g == 2)
		{
			_data1[i] = rand() % 2;
			_data2[i] = 1 - _data1[i];
		}
	}

	return std::vector<haplotype*>({new haplotype(_data1), new haplotype(_data2)});
}
