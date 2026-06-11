#include "TRandom3.h"

double random_gen() {

	double num = gRandom->Uniform(-1, 1);

	return num;
}
