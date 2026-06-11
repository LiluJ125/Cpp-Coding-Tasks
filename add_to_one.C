#include <TMath.h>
#include <iostream>
#include <string>

//add the digits of a number together until you get a single digit number

/*int add_to_one(std::string number) {

	int sum;

	std::cout << "Enter a number. ";
	std::cin >> number;

	while (number.length() > 1) {
		sum = 0;
		for (int i = 0; i < number.length(); i++) {
			sum = sum + (number[i] - '0');
	
		}
		int number = static_cast<int>(number);
		int sum = static_cast<int>(sum);
		number = sum;
	}
	return number;
}
*/

int add_to_one(int number) {

	int sum = 0;

	std::string number = std::to_string(number);

	for (int i = 0; i < number.length(); i++) {
		sum = sum + number[i];
	}
	if (sum > 9) {
		add_to_one(sum);
	}
	else {
		return sum;
	}
	return number;
}
