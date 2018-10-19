#include <iostream>

#include "models/genetic_algorithm.h"
#include <ctime>

int main()
{
	const int _h1_a[] = { 0,1,0,1,1,1,0 };
	const auto _h1 = new haplotype(_h1_a, 7);

	const int _h2_a[] = { 1,0,1,1,0,0,0 };
	const auto _h2 = new haplotype(_h2_a, 7);

	const int _h3_a[] = { 0,0,0,1,1,1,1 };
	const auto _h3 = new haplotype(_h3_a, 7);

	const int _h4_a[] = { 0,0,1,0,1,0,0 };
	const auto _h4 = new haplotype(_h4_a, 7);

	const int _h5_a[] = { 1,0,1,1,1,1,0 };
	const auto _h5 = new haplotype(_h5_a, 7);

	const int _h6_a[] = { 0,1,0,1,0,0,0 };
	const auto _h6 = new haplotype(_h6_a, 7);

	const auto _g1 = *_h1 + *_h2;
	const auto _g2 = *_h1 + *_h3;
	const auto _g3 = *_h1 + *_h4;
	const auto _g4 = *_h2 + *_h3;
	const auto _g5 = *_h2 + *_h4;
	const auto _g6 = *_h3 + *_h4;

	genotype* _genotypes[] = { _g1, _g2, _g3, _g4, _g5, _g6 };

	genetic_algorithm::run(std::vector<genotype*>(_genotypes, _genotypes + 6), 10);

	system("pause");

	//haplotype* _i1_a[] = { _h1, _h2, _h3, _h4, _h1, _h6 };
	//haplotype* _i2_a[] = { _h1, _h2, _h3, _h4, _h5, _h6 };

	//const auto _i1 = new individual(std::vector<haplotype*>(_i1_a, _i1_a + 4),
	//	std::vector<genotype*>(_genotypes, _genotypes + 6));

	//const auto _i2 = new individual(std::vector<haplotype*>(_i2_a, _i2_a + 6),
	//	std::vector<genotype*>(_genotypes, _genotypes + 6));

	//_i1->get_mappings();
	//_i2->get_mappings();

	return 0;
}
