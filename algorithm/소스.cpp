#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int CASE1 = -1;
const int CASE2 = 0;
const int CASE3 = 1;

int case1Cnt = 0;
int case2Cnt = 0;
int case3Cnt = 0;

int n;
vector<vector<int>> board;

void cnt(int r, int c, int size) {
	if (size == 1) {
		if (board[r][c] == CASE1) case1Cnt++;
		else if (board[r][c] == CASE2) case2Cnt++;
		else if (board[r][c] == CASE3) case3Cnt++;
		return;
	}

	bool allSame = true;
	for (int i = r; i < r + size; ++i) {
		for (int j = c; j < c + size; ++j) {
			if (board[i][j] != board[r][c]) {
				allSame = false;
				break;
			}
		}
		if (!allSame) break;
	}

	if (allSame) {
		if (board[r][c] == CASE1) case1Cnt++;
		else if (board[r][c] == CASE2) case2Cnt++;
		else if (board[r][c] == CASE3) case3Cnt++;
		return;
	}

	int nextSize = size / 3;
	cnt(r, c, nextSize); cnt(r, c + nextSize, nextSize); cnt(r, c + (nextSize*2), nextSize);
	cnt(r + nextSize, c, nextSize); cnt(r + nextSize, c + nextSize, nextSize); cnt(r+ nextSize, c + (nextSize * 2), nextSize);
	cnt(r + (nextSize * 2), c, nextSize); cnt(r + (nextSize * 2), c + nextSize, nextSize); cnt(r + (nextSize * 2), c + (nextSize * 2), nextSize);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		vector<int> row;
		for (int j = 0; j < n; ++j) {
			int input;
			cin >> input;
			row.push_back(input);
		}
		board.push_back(row);
	}

	cnt(0, 0, n);

	cout << case1Cnt << "\n";
	cout << case2Cnt << "\n";
	cout << case3Cnt;
	return 0;
}