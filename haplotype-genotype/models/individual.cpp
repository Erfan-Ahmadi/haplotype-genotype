#include "individual.h"

individual::individual(_In_ const std::vector<haplotype>& pData)
	: _haplotypes(pData)
{
}

individual::individual(
	_In_ const haplotype* pData,
	_In_ const int& pSize)
	: _haplotypes(std::vector<haplotype>(pData, pData + pSize))
{
}

individual::~individual()
{
	release();
}

float individual::get_fitness() const
{
	return (1.0f / _haplotypes.size());
}

void individual::release()
{
}
