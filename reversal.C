#include <TMath.h>
#include <iostream>
#include <string>

//reverse the digits of a given integer

std::string reversal(){

	std::string integer;
	std::string new_integer;

	std::cout << "Enter a number.";
	std::cin >> integer;

	for (int i = integer.length() - 1; i >= 0; i--){
		new_integer = new_integer + integer[i];
	}
	return new_integer;
}
