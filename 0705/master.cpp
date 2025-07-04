/*
R이 최대 10^9

각 사이클 별로 주기를 구해서 풀라는 거겠네
*/

#include <iostream>
#include <vector>

void Sim (std::vector<std::vector<int>>& mat, const int& start, const int& N, const int& M, const int& R) {
    // 한 사이클에서 원소의 개수: 2 * (N + M - 2)개
    int cur_rotations = R % (2 * (N + M - 2));

    for (int i = 0; i < cur_rotations; i++) {
        int temp = mat[start][start];
        // 맨 위의 행(start번 행)에서 우 -> 좌로 전파
        for (int c = start; c < start + M - 1; c++) {
            mat[start][c] = mat[start][c + 1];
        }
        // 맨 오른쪽 열(start + M - 1번 열)에서 하 -> 상으로 전파
        for (int r = start; r < start + N - 1; r++) {
            mat[r][start + M - 1] = mat[r + 1][start + M - 1];
        }
        // 맨 아래 행(start + N - 1번 행)에서 좌 -> 우로 전파
        for (int c = start + M - 1; c > start; c--) {
            mat[start + N - 1][c] = mat[start + N - 1][c - 1];
        }
        // 맨 좌측 열(start번 열)에서 상 -> 하로 전파
        for (int r = start + N - 1; r > start + 1; r--) {
            mat[r][start] = mat[r - 1][start];
        }
        // 원래 mat[start][start]값 대입
        mat[start + 1][start] = temp;
    }

    if (N - 2 > 0 && M - 2 > 0) {
        Sim(mat, start + 1, N - 2, M -2, R);
    }
}

int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M, R;
    std::cin >> N >> M >> R;

    std::vector<std::vector<int>> mat(N, std::vector<int> (M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> mat[i][j];
        }
    }

    Sim(mat, 0, N, M, R);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}