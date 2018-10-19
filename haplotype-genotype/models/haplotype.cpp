#include "haplotype.h"
#include <vector>

haplotype::haplotype(_In_ const std::vector<int>& pData) 
: _data(pData)
{
}

haplotype::haplotype(
	_In_ const int* pData,
	_In_ const int& pSize)
: _data(std::vector<int>(pData, pData + pSize))
{
}

haplotype::~haplotype()
{
	release();
}

genotype* haplotype::operator+(const haplotype& pSecond) const
{
	return get_merge_genotyped(pSecond);
}

genotype* haplotype::get_merge_genotyped(const haplotype& pSecond) const
{
	auto _genotype_data = std::vector<int>(this->_data.size());

	if (this->_data.size() != pSecond.get_data().size())
		return nullptr;

	for (auto i = 0; i < this->_data.size(); i++)
	{
		if (this->_data[i] == 1 && pSecond.get_data()[i] == 1)
			_genotype_data[i] = 1;
		else if (this->_data[i] == 0 && pSecond.get_data()[i] == 0)
			_genotype_data[i] = 0;
		else
			_genotype_data[i] = 2;
	}

	return new genotype(_genotype_data);
}

const std::vector<int>& haplotype::get_data() const
{
	return this->_data;
}

void haplotype::release()
{
	// Cleanup Memory
}
