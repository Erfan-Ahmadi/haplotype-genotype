#pragma once

#ifndef __POPULATION__ 
#define __POPULATION__

#include "individual.h"

class genetic_algorithm
{
public:
	static void run(
		_In_ std::vector<genotype*> pGenotypes,
		_In_ const int& pPopulationSize);

	~genetic_algorithm();

#pragma region Setters
#pragma endregion 

#pragma region Getters
	static const individual* get_population_fittest(_In_ const std::vector<individual*>& pPopulation);
#pragma endregion 

	static void release_population(_In_ std::vector<individual*>& pPopulation);

private:
	static std::vector<haplotype*> _get_generating_haplotypes(_In_ genotype* pGenotype);
};

#endif
