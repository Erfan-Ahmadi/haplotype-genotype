#pragma once

#ifndef __GENOTYPE__ 
#define __GENOTYPE__

#include <vector>

#define SAFE_RELEASE(x) if(x != nullptr) { x->release(); x = nullptr; }

class genotype
{
public:
	genotype(_In_ const std::vector<int>& pData);

	genotype(
		_In_ const int* pData,
		_In_ const int& pSize);

	bool operator==(const genotype& pRhs) const
	{
		return this->_data == pRhs.get_data();
	}

	//TODO: to string

	~genotype();

#pragma region Setters
#pragma endregion 

#pragma region Getters
	const std::vector<int>& get_data() const;
#pragma endregion 

	void release();

private:
	std::vector<int> _data;
};

#endif
