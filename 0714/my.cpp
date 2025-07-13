#include <stdio.h>
#include <iostream>
#include <utility>
#include <string>
#include <math.h>
#define MAX_VAL 11

void InputArr(int n, int m, int** arr, std::pair<int, int>& coin1, std::pair<int, int>& coin2) {
	
	int coinNum = 1;
	
	for ( int i = 0; i < n; i++ ) {
		
		arr[i] = new int [m];
			
		std::string arr_s;
		getline(std::cin, arr_s);
		
		for ( int j = 0; j < m; j++ ) {
			
			char c_data = arr_s[j];
			
			if ( c_data == 'o' ) {
				arr[i][j] = 0;
				if ( coinNum == 1 ) {
					coin1 = {i, j};
					coinNum += 1;
				} else coin2 = {i, j};
			} else if ( c_data == '.' ) arr[i][j] = 0;
			else arr[i][j] = -1;
		}
	}
	
}

void DeleteArr(int n, int** arr) {
	for (int i = 0; i < n; i++) delete[] arr[i];
	delete[] arr;
}

void GuardFunc(int x1, int y1, int x2, int y2, int** arr,
	std::pair<int, int>& coin1,
	std::pair<int, int>& coin2
) {
	
	if ( arr[x1][y1] == 0 ) {
		coin1.first = x1;
		coin1.second = y1;
	} 
	
	if ( arr[x2][y2] == 0 ) {
		coin2.first = x2;
		coin2.second = y2;
	}
	
}

void DFS(
	int n, 
	int m,
	int node,
	int count,
	int* answer,
	std::pair<int, int> coin1,
	std::pair<int, int> coin2,
	int** arr
) {
	
	count += 1;
	
	int coin1_x = coin1.first, coin1_y = coin1.second, coin2_x = coin2.first, coin2_y = coin2.second;
	
	// guard
	if ( node == 1 ) {
		coin1_x -= 1;
		coin2_x -= 1;
		
		if ( coin1_x == -1 && coin2_x != -1 ) {
			*answer = std::min(*answer, count);
			return;	
		}
		
		else if ( coin1_x != -1 && coin2_x == -1 ) {
			*answer = std::min(*answer, count);
			return;	
		}
		
		else if ( coin1_x != -1 && coin2_x != -1 ) GuardFunc(coin1_x, coin1_y, coin2_x, coin2_y, arr, coin1, coin2);
		
		else return;
	}
	
	else if ( node == 2 ) {
		coin1_x += 1;
		coin2_x += 1;
		
		if ( coin1_x == n && coin2_x != n ) {
			*answer = std::min(*answer, count);
			return;	
		}
		
		else if ( coin1_x != n && coin2_x == n ) {
			*answer = std::min(*answer, count);
			return;	
		}
		
		else if ( coin1_x != n && coin2_x != n ) GuardFunc(coin1_x, coin1_y, coin2_x, coin2_y, arr, coin1, coin2);
		
		else return;
	}
	
	else if ( node == 3 ) {
		coin1_y += 1;
		coin2_y += 1;
		
		if ( coin1_y == m && coin2_y != m ) {
			*answer = std::min(*answer, count);
			return;	
		}
		
		else if ( coin1_y != m && coin2_y == m ) {
			*answer = std::min(*answer, count);
			return;	
		}
		
		else if ( coin1_y != m && coin2_y != m ) GuardFunc(coin1_x, coin1_y, coin2_x, coin2_y, arr, coin1, coin2);
		
		else return;
	}
	
	else {
		coin1_y -= 1;
		coin2_y -= 1;
		
		if ( coin1_y == -1 && coin2_y != -1 ) {
			*answer = std::min(*answer, count);
			return;	
		}
		
		else if ( coin1_y != -1 && coin2_y == -1 ) {
			*answer = std::min(*answer, count);
			return;	
		}
		
		else if ( coin1_y != -1 && coin2_y != -1 ) GuardFunc(coin1_x, coin1_y, coin2_x, coin2_y, arr, coin1, coin2);
		
		else return;
	}
	
	if ( count == 10 ) return;
	
	for ( int new_node = 1; new_node < 5; new_node++ ) DFS(n, m, new_node, count, answer, coin1, coin2, arr);
	
}

int main(void) {
	
	// n, m
	int n, m;
	std::cin >> n >> m;
	getchar();
	
	// arr
	int** arr = new int*[n];
	std::pair<int, int> coin1;
	std::pair<int, int> coin2;
	InputArr(n, m, arr, coin1, coin2);
	
	// DFS
	int answer = MAX_VAL, count = 0;
	for ( int node = 1; node < 5; node++ ) DFS(n, m, node, count, &answer, coin1, coin2, arr);
	
	if ( answer == MAX_VAL ) answer = -1;
	
	std::cout << answer << std::endl;
	
	// delete arr
	DeleteArr(n, arr);
	
	return 0;
}