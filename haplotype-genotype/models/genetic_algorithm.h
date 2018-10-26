#pragma once

#ifndef __POPULATION__ 
#define __POPULATION__

#include "individual.h"

class genetic_algorithm
{
public:
	static void run(
		_In_ const std::vector<genotype*>& pGenotypes,
		_In_ const int& pPopulationSize,
		_In_ const float& pCrossoverRate = 0.8f,
		_In_ const float& pMutationRate = 0.01f,
		_In_ const bool& pElitism = true);

	~genetic_algorithm() = default;

private:

	static void initialize_population(
		_In_ const std::vector<genotype*>& pGenotypes,
		_In_ const int& pPopulationSize,
		_In_ std::vector<individual*>& pPopulation);

	static individual* tournament_selection(_In_ const std::vector<individual*>& pPopulation);

	static individual* crossover(
		_In_ const individual* pFirst,
		_In_ const individual* pSecond,
		_In_ const float& pCrossoverRate,
		_In_ const std::vector<genotype*>& pGenotypes);

	static individual* get_population_fittest(_In_ const std::vector<individual*>& pPopulation);

	static std::vector<haplotype*> get_generating_haplotypes(_In_ genotype* pGenotype);

	static individual* s_global_fittest;

	static void release_population(_In_ std::vector<individual*>& pPopulation);
};

#endif
