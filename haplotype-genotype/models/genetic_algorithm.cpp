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

		auto _individual = new individual();
		_individual->set_data(_haplotypes);
		pPopulation.push_back(_individual);
	}
}

void genetic_algorithm::mutate_individual(
	_In_ const std::vector<genotype*>& pGenotypes,
	_In_ individual** pIndividual)
{
	auto _rand_position = rand() % (*pIndividual)->get_data()->size();

	if (_rand_position % 2 != 0)
		_rand_position--;

	const auto _gen = get_generating_haplotypes(pGenotypes[_rand_position / 2]);

	(*pIndividual)->set_data_at(_rand_position, _gen[0]);
	(*pIndividual)->set_data_at(_rand_position + 1, _gen[1]);
	(*pIndividual)->calculate_fitness();
}

void genetic_algorithm::mutation(
	_In_ const std::vector<genotype*>& pGenotypes,
	_In_ const float& pMutationRate,
	_In_ const std::vector<individual*>& pPopulation)
{
	for (auto i = 0; i < pPopulation.size(); i++)
	{
		auto _individual = pPopulation[i];

		const auto _prob = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		if (_prob > pMutationRate)
			continue;

		mutate_individual(pGenotypes, &_individual);
	}
}

void genetic_algorithm::run(
	_In_	const std::vector<genotype*>& pGenotypes,
	_In_	const int& pPopulationSize,
	_In_	const int& pIterationCount,
	_In_	const int& pMaxRep,
	_In_	const float& pCrossoverRate,
	_In_	const float& pMutationRate,
	_In_	const bool& pElitism)
{
	srand(time(nullptr));

	std::vector<individual*> _population;

	const auto _data_length = pGenotypes[0]->_data.size();

	auto _elitism_offset = 0;

	std::cout << "Initializing..." << std::endl;

	initialize_population(pGenotypes, pPopulationSize, _population);


	s_global_fittest = _population[0];

	auto _terminate = false;

	auto _iterations = 0;

	auto _repeat = 0;

	std::cout << "Running..." << std::endl;

	while (!_terminate)
	{
		// Selection 

		auto _next_population = std::vector<individual*>();

		if (pElitism) {
			auto _elite = new individual();
			auto _hap_data = std::vector<haplotype*>(_population[0]->get_data()->size());

			for (int i = 0; i < _hap_data.size(); i++)
				_hap_data[i] = new haplotype(*_population[0]->get_data_at(i));

			_elite->set_data(_hap_data);

			_next_population.insert(_next_population.begin(), _elite);
			_elitism_offset = 1;
		}
		else {
			_elitism_offset = 0;
		}

		// Crossover

		for (auto i = _elitism_offset; i < _population.size(); i++)
		{
			const auto _first = tournament_selection(_population);
			const auto _second = tournament_selection(_population);
			auto _new_individual = crossover(_first, _second, pCrossoverRate, pGenotypes);
			_next_population.push_back(_new_individual);
		}

		release_population(_population);
		_population = _next_population;


		// Mutation 
		mutation(pGenotypes, pMutationRate, _population);


		// Local Optimization

		auto _sum = 0.0, _standard_deviation = 0.0;

		int i;

		for (i = 0; i < pPopulationSize; ++i)
		{
			_sum += _population[i]->get_fitness();
		}

		const auto _mean = _sum / pPopulationSize;

		for (i = 0; i < pPopulationSize; ++i)
			_standard_deviation += pow(_population[i]->get_fitness() - _mean, 2);

		_standard_deviation = sqrt(_standard_deviation / pPopulationSize);

		const auto _local_optimization_rate = 0.3f;
		const auto _local_search_steps = 5;
		const auto _k = 0.9f;

		for (auto& _indi : _population)
		{
			if (rand() / double(RAND_MAX) < _local_optimization_rate)
			{
				for (int j = 0; j < _local_search_steps; j++)
				{
					const auto& _temp_indi = _indi->copy();
					mutate_individual(pGenotypes, &_indi);
					const auto _diff = _temp_indi->get_fitness() - _indi->calculate_fitness();
					if (_diff > 0)
					{
						const auto _dev = exp(-(_k * _diff) / _standard_deviation);
						if (rand() / double(RAND_MAX) > _dev)
						{
							_indi->release();
							_indi = _temp_indi;
						}
						else
						{
							_temp_indi->release();
						}
					}
					else
					{
						_temp_indi->release();
					}
				}
			}
		}

		// Get fittest
		const auto _population_fittest = get_population_fittest(_population);

		if (s_global_fittest->get_fitness() < _population_fittest->get_fitness())
		{
			s_global_fittest = get_population_fittest(_population)->copy();
			_repeat = 0;
		}
		else
		{
			_repeat++;
		}

		std::cout << "Iteration " << _iterations << " : " << s_global_fittest->get_data()->size() - s_global_fittest->get_fitness() << std::endl;

		if (_repeat >= pMaxRep)
		{
			_terminate = true;
			break;
		}

		if (_iterations++ >= pIterationCount)
		{
			_terminate = true;
			break;
		}
	}

	//release_population(_population);
}

individual* genetic_algorithm::tournament_selection(_In_ const std::vector<individual*>& pPopulation)
{
	auto _tournament = std::vector<individual*>();

	const auto _tournament_size = 2;

	for (auto i = 0; i < _tournament_size; i++)
	{
		_tournament.push_back(pPopulation[rand() % pPopulation.size()]);
	}

	return get_population_fittest(_tournament);
}

individual* genetic_algorithm::crossover(
	_In_ const individual* pFirst,
	_In_ const individual* pSecond,
	_In_ const float& pCrossoverRate,
	_In_ const std::vector<genotype*>& pGenotypes)
{
	auto _new_individual = new individual();
	auto _new_data = std::vector<haplotype*>();

	for (auto i = 0; i < pFirst->get_data()->size(); i += 2)
	{
		if (rand() % 2 == 0)
		{
			_new_data.push_back(new haplotype(*pFirst->get_data_at(i)));
			_new_data.push_back(new haplotype(*pFirst->get_data_at(i + 1)));
		}
		else
		{
			_new_data.push_back(new haplotype(*pSecond->get_data_at(i)));
			_new_data.push_back(new haplotype(*pSecond->get_data_at(i + 1)));
		}
	}

	_new_individual->set_data(_new_data);
	return _new_individual;
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
	pPopulation.shrink_to_fit();
}

std::vector<haplotype*> genetic_algorithm::get_generating_haplotypes(genotype* pGenotype)
{
	auto _data1 = std::vector<bool>(pGenotype->_data.size());
	auto _data2 = std::vector<bool>(pGenotype->_data.size());

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
