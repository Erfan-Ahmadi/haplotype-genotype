#include "genetic_algorithm.h"
#include <stdlib.h>
#include <time.h>   
#include <iostream>
#include <algorithm>

individual* genetic_algorithm::s_global_fittest = nullptr;

void genetic_algorithm::initialize_population(
	_In_ const std::vector<genotype*>& pGenotypes,
	_In_ const int& pPopulationSize,
	_In_ std::vector<individual*>& pPopulation)
{
	for (auto i = 0; i < pPopulationSize; i++)
	{
		auto _haplotypes = std::vector<haplotype*>();

		for (const auto& _genotype : pGenotypes)
		{
			const auto _generating_haplotypes = get_generating_haplotypes(_genotype);
			_haplotypes.insert(_haplotypes.end(), _generating_haplotypes.begin(), _generating_haplotypes.end());
		}

		auto _individual = new individual(pGenotypes);
		_individual->set_data(_haplotypes);
		pPopulation.push_back(_individual);
	}
}

void genetic_algorithm::run(
	_In_ const std::vector<genotype*>& pGenotypes,
	_In_ const int& pPopulationSize,
	_In_ const float& pCrossoverRate,
	_In_ const float& pMutationRate,
	_In_ const bool& pElitism)
{
	srand(time(nullptr));

	std::vector<individual*> _population;

	const auto _data_length = pGenotypes[0]->_data.size();

	auto _elitism_offset = 0;

	initialize_population(pGenotypes, pPopulationSize, _population);
	s_global_fittest = _population[0];

	auto _terminate = false;

	auto _iterations = 0;
	const auto _max_iterations = 100;

	while (!_terminate)
	{
		// Selection 

		auto _next_population = std::vector<individual*>();

		if (pElitism) {
			_next_population.push_back(new individual(*get_population_fittest(_population)));
			_elitism_offset = 1;
		}
		else {
			_elitism_offset = 0;
		}

		// Crossover

		for(auto i = _elitism_offset; i < _population.size(); i++)
		{
			const auto _first = tournament_selection(_population);
			const auto _second = tournament_selection(_population);
			auto _new_individual = crossover(_first, _second, pCrossoverRate);
			_next_population.push_back(_new_individual);
		}

		release_population(_population);
		_population = _next_population;

		// Mutation 

		s_global_fittest = get_population_fittest(_population);

		std::cout << s_global_fittest->get_fitness() << std::endl;

		if (_iterations++ > _max_iterations)
		{
			_terminate = true;
			break;
		}
	}
	release_population(_population);
}

individual* genetic_algorithm::tournament_selection(_In_ const std::vector<individual*>& pPopulation)
{
	auto _tournament = std::vector<individual*>();

	const auto _tournament_size = 3;

	for (auto i = 0; i < _tournament_size; i++)
	{
		_tournament.push_back(pPopulation[rand() % pPopulation.size()]);
	}

	return get_population_fittest(_tournament);
}

individual* genetic_algorithm::crossover(
	_In_ const individual* pFirst,
	_In_ const individual* pSecond,
	_In_ const float& pCrossoverRate)
{
	return new individual(*pFirst);
}

individual* genetic_algorithm::get_population_fittest(_In_ const std::vector<individual*>& pPopulation)
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

std::vector<haplotype*> genetic_algorithm::get_generating_haplotypes(genotype* pGenotype)
{
	auto _data1 = std::vector<int>(pGenotype->_data.size());
	auto _data2 = std::vector<int>(pGenotype->_data.size());

	for (auto i = 0; i < pGenotype->_data.size(); i++)
	{
		const auto _g = pGenotype->_data[i];

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

	return std::vector<haplotype*>({ new haplotype{_data1}, new haplotype {_data2} });
}
