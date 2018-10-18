#include "genotype.h"

genotype::genotype(_In_ const std::vector<int>& pData) : _data(pData)
{
}

genotype::genotype(
	_In_ const int* pData,
	_In_ const int& pSize)
	: _data(std::vector<int>(pData, pData + pSize))
{
}

genotype::~genotype()
{
	release();
}

const std::vector<int>& genotype::get_data() const
{
	return this->_data;
}

void genotype::release()
{
	// Cleanup Memory
}
