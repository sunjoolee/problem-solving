#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> board(9, vector<int>(9, 0));

vector<vector<bool>> rowCheck(9, vector<bool>(10, false));
vector<vector<bool>> colCheck(9, vector<bool>(10, false));

//스도투 판 9등분 
//0 1 2
//3 4 5
//6 7 8
vector<vector<bool>> blockCheck(9, vector<bool>(10, false));

int blockR[9] = { 0, 0, 0, 3, 3, 3, 6, 6, 6 }; 
int blockC[9] = { 0, 3, 6, 0, 3, 6, 0, 3, 6 };

bool solved() {
	for (int i = 0; i < 9; ++i) {
		for (int num = 1; num <= 9; ++num) {
			if (rowCheck[i][num] == false) return false;
			if (colCheck[i][num] == false) return false;
			if (blockCheck[i][num] == false) return false;
		}
	}
	return true;
}

void solve() {
	//basecase
	if (solved()) {
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				cout << board[i][j] << " ";
			}
			cout << "\n";
		}
		exit(0);
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "------------\n";

	for (int blockNum = 0; blockNum < 9; ++blockNum) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				int r = blockR[blockNum] + i;
				int c = blockC[blockNum] + j;

				//스도쿠 빈칸인 경우 가능한 모든 숫자 삽입
				if (board[r][c] == 0) {
					for (int num = 1; num <= 9; ++num) {
							if (rowCheck[r][num]) continue;
							if (colCheck[c][num]) continue;
							if (blockCheck[blockNum][num]) continue;

							rowCheck[r][num] = true;
							colCheck[c][num] = true;
							blockCheck[blockNum][num] = true;

							board[r][c] = num;
							solve();
							board[r][c] = 0;

							rowCheck[r][num] = false;
							colCheck[c][num] = false;
							blockCheck[blockNum][num] = false;
					}
					return;
				}
			}
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			int input;
			cin >> input;
			board[i][j] = input;

			rowCheck[i][input] = true;
			colCheck[j][input] = true;
		}
	}

	for (int blockNum = 0; blockNum < 9; ++blockNum) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				int r = blockR[blockNum] + i;
				int c = blockC[blockNum] + j;

				blockCheck[blockNum][board[r][c]] = true;
			}
		}
	}

	solve();

	return 0;
}