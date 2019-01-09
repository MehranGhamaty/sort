#include <iostream>
#include <vector>

#include "sort.hpp"

int main(int argc, char *argv[]) {
	std::vector<int> A = {2,5,3,0,2,3,0,3};
	int k = 5;

	
	for(int e : A) {std::cout << e << "\t"; } std::cout << std::endl;

	std::vector<int> B = countingsort<int>(A, k);

	for(int e : B) {std::cout << e << "\t"; } std::cout << std::endl;

	return 0;
}
