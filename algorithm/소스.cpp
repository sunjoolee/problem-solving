#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

vector<vector<int>> board;

bool correct() {
	for (int i = 0; i < 9; ++i) {
		//한 행에 같은 숫자 중복되지 않는지 확인
		string maskRow = "000000000";

		//한 열에 같은 숫자 중복되지 않는지 확인	
		string maskCol = "000000000";

		for (int j = 0; j < 9; ++j) {
			if (board[i][j] != 0) {
				if (maskRow[board[i][j] - 1] != '0') return false;
				maskRow[board[i][j] - 1] = '1';
			}

			if (board[j][i] != 0) {
				if (maskCol[board[j][i] - 1] != '0') return false;
				maskCol[board[j][i] - 1] = '1';
			}
		}
	}

	//한 칸에 같은 숫자 중복되지 않는지 확인
	for (int k1 = 0; k1 < 9; k1 += 3) {
		for (int i = 0 + k1; i < 3 + k1; ++i) {
			for (int k2 = 0; k2 < 9; k2 += 3) {
				string mask = "000000000";
				for (int j = 0 + k2; j < 3 + k2; ++j) {
					if (board[i][j] != 0) {
						if (mask[board[i][j] - 1] != '0') return false;
						mask[board[i][j] - 1] = '1';
					}
				}
			}
		}
	}
	return true;
}

bool finished() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (board[i][j] == 0) return false;
		}
	}
	return true;
}

void dfs() {
	if (finished()) {
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				cout << board[i][j];
			}
			cout << "\n";
		}

		exit(0);
	}

	bool change = false;
	for (int i = 0; i < 9; ++i) {
		if (change) return;
		for (int j = 0; j < 9; ++j) {
			if (change) return;

			if (board[i][j] == 0) {
				for (int k = 0; k < 9; ++k) {
					board[i][j] = k;
					if (correct()) {
						dfs();
					}
					board[i][j] = 0;
				}
				change = true;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	for (int i = 0; i < 9; ++i) {
		string str;
		vector<int> v;

		cin >> str;
		
		for (int j = 0; j < 9; ++j) {
			v.push_back(str[j] - '0');
		}
		board.push_back(v);
	}

	dfs();
	return 0;
}