/*
Source			 : Please direct any bugs to https://github.com/Erfan-Ahmadi/haplotype-genotype issues
Developers		 : Erfan Ahmadi
*/

#pragma once

#ifndef __POPULATION__ 
#define __POPULATION__

#include "individual.h"

class genetic_algorithm
{
public:
	static void run(
		_In_	const std::vector<genotype*>& pGenotypes,
		_In_	const int& pPopulationSize,
		_In_	const int& pIterationCount,
		_In_	const int& pMaxRep,
		_In_	const float& pCrossoverRate,
		_In_	const float& pMutationRate,
		_In_	const bool& pElitism = true);

	static individual* s_global_fittest;

	~genetic_algorithm() = default;

private:

	static void initialize_population(
		_In_ const std::vector<genotype*>& pGenotypes,
		_In_ const int& pPopulationSize,
		_In_ std::vector<individual*>& pPopulation);

	static void mutate_individual(
		_In_ const std::vector<genotype*>& pGenotypes,
		_In_ individual** pIndividual);

	static void mutation(
		_In_ const std::vector<genotype*>& pGenotypes,
		_In_ const float& pMutationRate,
		_In_ const std::vector<individual*>& _population);

	static individual* tournament_selection(_In_ const std::vector<individual*>& pPopulation);

	static individual* crossover(
		_In_ const individual* pFirst,
		_In_ const individual* pSecond,
		_In_ const float& pCrossoverRate,
		_In_ const std::vector<genotype*>& pGenotypes);

	static individual* get_population_fittest(_In_ const std::vector<individual*>& pPopulation);

	static std::vector<haplotype*> get_generating_haplotypes(_In_ genotype* pGenotype);

	static void release_population(_In_ std::vector<individual*>& pPopulation);
};

#endif
