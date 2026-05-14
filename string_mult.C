#include <TMath.h>
#include <iostream>

void string_mult(int num1, int num2) {

	int mult = num1 * num2;

	std::cout << std::to_string(num1) + "X" + std::to_string(num2) + "=" + std::to_string(mult) << endl;
}
