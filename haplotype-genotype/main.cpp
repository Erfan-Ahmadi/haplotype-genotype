/*
Source			 : Please direct any bugs to https://github.com/Erfan-Ahmadi/haplotype-genotype issues
Developers		 : Erfan Ahmadi
*/

#include <iostream>

#include "models/genetic_algorithm.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>

genotype* line_to_genotype(
	_In_ const char* pLine,
	_In_ const int& pSize);

bool is_valid_for_genotype(
	_In_ std::vector<genotype*>& pGenotypes,
	_In_  const std::vector<haplotype*>& pHaplotypes);

template <class T>
std::string array_to_str(_In_ std::vector<T>& pData)
{
	std::string _result;

	for (T _data : pData)
	{
		_result += std::to_string(_data);
	}
	
	return _result;
}

template <class T>
void get_input(_Out_ T& pOut, _In_ const T& pDeafult, _In_z_ const std::string& name)
{
	std::cout << "Enter " << name << " (default = " << pDeafult << ") :";
	try
	{
		std::cin >> pOut;
	}
	catch (int _exception)
	{
		pOut = pDeafult;
	}
}

int main()
{
	auto _genotypes = std::vector<genotype*>();

	const auto _get_input = true;

	std::string _file_name;

	if (_get_input)
	{
		std::cout << "Enter File Dir : ";
		std::cin >> _file_name;
	}
	else
	{
		_file_name = "genotype2.txt";
	}

	int _genotype_size;
	std::string _line;
	std::ifstream _sample_data_file(_file_name);

	{
		if (_sample_data_file.is_open())
		{
			while (getline(_sample_data_file, _line))
			{
				try
				{
					_genotype_size = _line.size();
					_genotypes.push_back(line_to_genotype(_line.c_str(), _line.size()));
				}
				catch (int _exception)
				{
					std::cout << "Unable to parse genotypes" << std::endl;
					system("pause");
					return 0;
				}
			}

			_sample_data_file.close();
		}
		else
		{
			std::cout << "Unable to open file" << std::endl;
			system("pause");
			return 0;
		}

		if (_genotypes.empty())
		{
			std::cout << "Unable to parse genotypes" << std::endl;
			system("pause");
			return 0;
		}
	}

	const auto _genotypes_size = _genotypes.size();

	float _crossover_rate;
	float _mutation_rate;
	int _population_size;
	int _iterations;
	int _max_rep;

	const auto _default_crossover_rate = 0.8f;
	const auto _default_mutation_rate = 0.1f;
	const auto _default_population_size = 5000;
	const auto _default_iterations = 1000;
	const auto _default_max_rep = 25;

	if (_get_input)
	{
		get_input(_crossover_rate, _default_crossover_rate, "Crossover Rate");
		get_input(_mutation_rate, _default_mutation_rate, "Mutation Rate");
		get_input(_population_size, _default_population_size, "Population Size");
		get_input(_iterations, _default_iterations, "Iterations Count");
		get_input(_max_rep, _default_max_rep, "Max Rep Count");
	}
	else
	{
		_crossover_rate = _default_crossover_rate;
		_mutation_rate = _default_mutation_rate;
		_population_size = _default_population_size;
		_iterations = _default_iterations;
		_max_rep = _default_max_rep;
	}

	const auto _start_time = std::chrono::system_clock::now();

	//RUN ALGORITHM HERE

	std::cout << "Crossover Rate		= " << _crossover_rate << std::endl;
	std::cout << "Mutation Rate		= " << _mutation_rate << std::endl;
	std::cout << "Iteration Count		= " << _iterations << std::endl;
	std::cout << "Population Size		= " << _population_size << std::endl;

	std::cout << std::endl;

	genetic_algorithm::run(_genotypes, _population_size, _iterations, _max_rep, _crossover_rate, _mutation_rate);

	const auto _end_time = std::chrono::system_clock::now();

	const auto _output = genetic_algorithm::s_global_fittest->get_hapolotypes_without_repetition();

	const auto _output_file_name = "haplotypes.out";
	{

		std::cout << "-Data Size: " << _genotypes_size << std::endl;

		std::cout << "-Each Genotype Size: " << _genotype_size << std::endl;

		std::cout << "-Population Size: " << _population_size << std::endl;

		std::cout << "-Geneteic Algorithm Duration: " <<
			std::chrono::duration_cast<std::chrono::milliseconds>(_end_time - _start_time).count() << " mili seconds." << std::endl;

		std::cout << "- Output Haplotypes Size: " << _output.size() << std::endl;

		const std::string is_valid_str = (is_valid_for_genotype(_genotypes, _output))
			? "Is Valid" : "Not Valid (Algorithm Not Correct)";

		std::cout << "- Validity Check : " << is_valid_str << std::endl;

		std::cout << " - Output File : " << _output_file_name << std::endl;
	}

	// Write To File

	std::ofstream _output_file;
	_output_file.open(_output_file_name);

	for (const auto& _haplo : _output)
	{
		_output_file << array_to_str(_haplo->_data) << std::endl;
	}

	_output_file.close();

	system("pause");

	return 0;
}

bool is_valid_for_genotype(
	_In_ std::vector<genotype*>& pGenotypes,
	_In_  const std::vector<haplotype*>& pHaplotypes)
{
	auto _does_generate = std::vector<bool>(pGenotypes.size());

	for (int i = 0; i < pHaplotypes.size(); i++)
	{
		const auto _left = pHaplotypes[i];
		for (int j = i; j < pHaplotypes.size(); j++)
		{
			const auto _right = pHaplotypes[j];

			for (int k = 0; k < pGenotypes.size(); k++)
			{
				if (!_does_generate[k] && (*_left + *_right)->_data == pGenotypes[k]->_data)
					_does_generate[k] = true;
			}
		}
	}

	for (const auto& _does : _does_generate)
		if (!_does)
			return false;

	return true;
}

genotype* line_to_genotype(
	_In_ const char* pLine,
	_In_ const int& pSize)
{
	auto _genotype_data = std::vector<char>(pSize);

	for (auto i = 0; i < pSize; i++)
	{
		_genotype_data[i] = pLine[i] - '0';
	}

	return new genotype{ _genotype_data };
}