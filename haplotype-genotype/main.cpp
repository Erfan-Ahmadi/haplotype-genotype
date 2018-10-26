#include <iostream>

#include "models/genetic_algorithm.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>

genotype* line_to_genotype(const char* pLine, const int& pSize);

int main()
{
	auto _genotypes = std::vector<genotype*>();

	std::string _line;
	std::ifstream _sample_data_file("sample_datas/genotype2.txt");

	auto _genotype_size = 20;

	if (_sample_data_file.is_open())
	{
		while (getline(_sample_data_file, _line))
		{
			_genotype_size = _line.size();
			_genotypes.push_back(line_to_genotype(_line.c_str(), _line.size()));
		}

		_sample_data_file.close();
	}
	else std::cout << "Unable to open file";

	const auto _population_size = 50;
	const auto _genotypes_size = _genotypes.size();

	for(auto i = 0; i < _genotypes_size; i++)
	{
		auto _random_data = std::vector<int>(_genotype_size);

		for(auto j = 0; j < _genotype_size; j++)
		{
			_random_data[j] = rand() % 3;
		}

		_genotypes[i] = new genotype{ _random_data };
	}

	const auto _start_time = std::chrono::system_clock::now();

	//RUN ALGORITHM HERE
	genetic_algorithm::run(_genotypes, _population_size);

	const auto _end_time = std::chrono::system_clock::now();

	std::cout << "- Random Data Size: " << _genotypes_size << std::endl;
	std::cout << "- Each Genotype Size: " << _genotype_size << std::endl;
	std::cout << "- Population Size: " << _population_size << std::endl;
	std::cout << "- Geneteic Algorithm Duration: " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(_end_time - _start_time).count() << " mili seconds." << std::endl;
	std::cout << "- Best Fitness: " << "" << std::endl;

	system("pause");

	return 0;
}

genotype* line_to_genotype(const char* pLine, const int& pSize)
{
	auto _genotype_data = std::vector<int>(pSize);

	for (auto i = 0; i < pSize; i++)
	{
		_genotype_data[i] = pLine[i] - '0';
	}

	return new genotype{ _genotype_data };
}