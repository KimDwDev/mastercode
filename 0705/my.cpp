#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>

void InputArr(int n, int m, int** arr) {
	for (int i = 0; i < n; i++) {
		arr[i] = new int [m];
		
		std::string arr_s;
		getline(std::cin, arr_s);
		std::istringstream iss(arr_s);
		
		int value, j = 0;
		while ( iss >> value ) arr[i][j++] = value;
	}
}

void DeleteArr(int n, int** arr) {
	for (int i = 0; i < n; i++) delete[] arr[i];
	delete[] arr;
}

class SimulationClass {
	
	public:
		SimulationClass(int n_, int m_, int r_, int** arr_) : n(n_), m(m_), r(r_), arr(arr_) {}
		
		void Start() {
			
			int a = n, b = m, init = 0;
			int** newArr = new int* [n];
			for ( int i = 0; i < n; i++ ) newArr[i] = new int [m];
			
			// range
			while ( a > 0 && b > 0 ) {
				
				//range
				std::vector<std::array<int, 2>> totalArr;
				Range(a, b, init, totalArr);
				
				// simulation
				Simulation(a, b, totalArr, newArr);
				
				init += 1;
				a -= 2;
				b -= 2;
			}
			
			for ( int i = 0; i < n; i++ ) {
				for ( int j = 0; j < m; j++ ) std::cout << newArr[i][j] << " ";
				std::cout << std::endl;
			}
			
			for ( int i = 0; i < n; i++ ) delete[] newArr[i];
			delete[] newArr;
		}
		
		// a -> row, b -> col
		void Range(const int a, const int b, const int init, std::vector<std::array<int, 2>>& totalArr ) {
			int x = init, y = init;
			
			totalArr.reserve(2 * (a + b - 2));
			std::array<int, 2> current;
			
			for ( int i = 0; i < 2 * (a + b - 2); i++ ) {
				
				// 1
				if (i < a-1) {
					current[0] = init + i;
					current[1] = init;
				}
				
				// 2
				else if (i >= a-1 && i < a + b - 2) {
					current[0] = init + a - 1;
					current[1] = init + i - (a-1);
				}
				
				// 3
				else if (i >= a + b - 2 && i < (2 * a + b - 3) ) {
					current[0] = init + a - 1 - (i - a - b + 2 );
					current[1] = init + b - 1;
				}
				
				// 4 
				else {
					current[0] = init;
					current[1] = init + b - 1 - ( i - (2 * a + b - 3)); 
				}
				totalArr.push_back(current);
			}
		}
		
		void Simulation(const int a, const int b, std::vector<std::array<int, 2>>& totalArr, int** newArr) {
			
			// init
			std::vector<std::array<int, 2>> copyArr;
			const int total = 2 * ( a + b - 2 );
			const int totalR = r % total;
			
			// simnulation
			for ( int i = 0; i < total; i ++ ) {
				int current = (i + totalR) % total;
				copyArr.push_back(totalArr[current]);
			}
			
			// answer
			for ( int i = 0; i < total; i++ ) {
				
				std::array<int, 2> currentValue = totalArr[i];
				std::array<int, 2> newValue = copyArr[i];
				
				newArr[newValue[0]][newValue[1]] = arr[currentValue[0]][currentValue[1]];
			}
		}
	
	private:
		int n;
		int m;
		int r;
		int** arr;
};

int main(void) {
	
	// n, m, r
	int n, m, r;
	std::cin >> n >> m >> r;
	getchar();
	
	// arr
	int** arr = new int* [n];
	InputArr(n, m, arr);
	
	// class
	SimulationClass sc(n, m, r, arr);
	
	sc.Start();
		
	// delete arr
	DeleteArr(n, arr);
	
	return 0;
}