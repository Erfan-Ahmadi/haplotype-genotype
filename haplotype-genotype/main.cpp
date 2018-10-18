#include <iostream>

#include "models/genotype.h"
#include "models/haplotype.h"
#include "models/individual.h"

int main()
{
	const int _h1_a[] = { 0,1,1,0,1 };
	const auto _h1 = new haplotype(_h1_a, 5);
	const int _h2_a[] = { 0,1,0,1,0 };
	const auto _h2 = new haplotype(_h2_a, 5);

	const haplotype _i1_a[] = { *_h1, *_h2 };
	const auto _i1 = new individual(_i1_a, 2);

	const auto _g1 = *_h1 + *_h2;

	_i1->is_valid_for_genotype(_g1, 1);

	return 0;
}
