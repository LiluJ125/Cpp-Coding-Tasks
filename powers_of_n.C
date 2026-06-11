#include <TMath.h>
#include <iostream>

int powers_of_n() {

	int x;
	int n;

	std::cout << "Enter a base ";
	std::cin >> x;
	std::cout << "Enter a power ";
	std::cin >> n;

	int result = std::pow(x, n);

	return result;
}
