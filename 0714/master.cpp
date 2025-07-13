#include <iostream>
#include <algorithm>
#include <queue>
#include <array>
using namespace std;

string s[30];
int N, M;
int dist[410][410];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

bool chk(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < M;
}

int coor(int x, int y) {
	return x * M + y;
}

void solve() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> s[i];
	}

	int x = -1, y = -1, z = -1, w = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (s[i][j] == 'o') {
				if (x == -1) {
					x = i;
					y = j;
				}
				else {
					z = i;
					w = j;
				}
				s[i][j] = '.';
			}
		}
	}

	queue<array<int, 4>> Q;
	Q.push({ x, y, z, w });
	dist[coor(x, y)][coor(z, w)] = 1;

	while (!Q.empty()) {
		auto [a, b, c, d] = Q.front();
		Q.pop();

		if (dist[coor(a, b)][coor(c, d)] > 10) {
			cout << "-1\n";
			return;
		}

		for (int i = 0; i < 4; i++) {
			int X = a + dx[i];
			int Y = b + dy[i];
			if (!chk(X, Y)) {
				X = N;
				Y = 0;
			}
			else if (s[X][Y] == '#') {
				X = a;
				Y = b;
			}
			int Z = c + dx[i];
			int W = d + dy[i];
			if (!chk(Z, W)) {
				Z = N;
				W = 0;
			}
			else if (s[Z][W] == '#') {
				Z = c;
				W = d;
			}

			if (!chk(X, Y) && !chk(Z, W)) {
				continue;
			}

			if (!chk(X, Y) || !chk(Z, W)) {
				cout << dist[coor(a, b)][coor(c, d)] << '\n';
				return;
			}

			if (dist[coor(X, Y)][coor(Z, W)]) {
				continue;
			}

			dist[coor(X, Y)][coor(Z, W)] = dist[coor(a, b)][coor(c, d)] + 1;
			Q.push({ X, Y, Z, W });
		}
	}

	cout << "-1\n";
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
	return 0;
}