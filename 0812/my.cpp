#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <limits.h>

void InputArr(int* arr) {
	std::string arr_s;
	getline(std::cin, arr_s);
	std::istringstream iss(arr_s);
	
	int value, i = 0;
	while ( iss >> value ) arr[i++] = value;
}

class BruteForce {
	
	public:
		BruteForce(int n_, int* arr_) : n(n_), arr(arr_) {}
		
		void Start() {
			BFS();
			
			std::cout << answer << std::endl;
		}
	
	private:
		int n;
		int* arr;
		int answer = 0;
		
		void SearchFunc(int& MIN_VAL, int i) {
			
			int& targetNumber = arr[i];
			
			if ( (targetNumber % 2) == 1) {
				targetNumber -= 1;
				answer += 1;
			}
			
			if ( targetNumber != 0 && MIN_VAL > targetNumber ) MIN_VAL = targetNumber;
		}
		
		void UpdateFunc() {
			for ( int i = 0; i < n; i++ ) arr[i] /= 2;	
			answer += 1;
		}
		
		void BFS() {
			
			while (true) {
				
				int MIN_VAL = INT_MAX;
				for ( int i = 0; i < n; i++ ) SearchFunc(MIN_VAL, i); // search
				
				if ( MIN_VAL == INT_MAX ) break; // stopPoint
				
				UpdateFunc();
			}
			
		}
};

int main(void) {
	
	// n
	int n;
	std::cin >> n;
	getchar();
	
	// arr
	int* arr = new int[n];
	InputArr(arr);
	
	// class
	BruteForce bf(n, arr);
	bf.Start();
	
	// delete arr
	delete[] arr;
	
	return 0;
}