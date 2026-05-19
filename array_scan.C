#include <TMath.h>
#include <iostream>

//check for a missing number in an array

int array_scan() {

	int n;
	int entry;
	arr[n] = {};

	std::cout << "Enter the size of the array";
	std::cin >> n;

	for (i = 0; i == n; i++) {
		std::cout << "Enter array values";
		std::cin >> entry;

		arr[i] = entry;
	}

	bool num_check;
	bool ent_in = 
	for (num = 1; num == n; num++) {
		for (ent = 0; ent == n; ent++) {
			if (arr[ent] == num) {
				num_check = true;
				break;
			}
		}
	}
	return missing;
}
