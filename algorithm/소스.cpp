#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

set<vector<vector<int>>> visited;

bool correct(vector<vector<int>> board) {

	//한 행에 같은 숫자 중복되지 않는지 확인
	for (int i = 0; i < 9; ++i) {
		int maskRow[10] = { 0 };

		for (int j = 0; j < 9; ++j) {
			if (board[i][j] != 0) {
				if (maskRow[board[i][j]] != 0) return false;
				maskRow[board[i][j]] = 1;
			}
		}
	}

	//한 열에 같은 숫자 중복되지 않는지 확인
	for (int j = 0; j < 9; ++j) {
		int maskCol[10] = { 0 };

		for (int i = 0; i < 9; ++i) {
			if (board[i][j] != 0) {
				if (maskCol[board[i][j]] != 0) return false;
				maskCol[board[i][j]] = 1;
			}
		}
	}

	//한 칸에 같은 숫자 중복되지 않는지 확인
	for (int k1 = 0; k1 < 9; k1 += 3) {
		for (int i = 0 + k1; i < 3 + k1; ++i) {
			for (int k2 = 0; k2 < 9; k2 += 3) {
				int mask[10] = { 0 };
				for (int j = 0 + k2; j < 3 + k2; ++j) {
					if (board[i][j] != 0) {
						if (mask[board[i][j]] != 0) return false;
						mask[board[i][j]] = 1;
					}
				}
			}
		}
	}

	return true;
}

bool finished(vector<vector<int>> board) {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (board[i][j] == 0) return false;
		}
	}
	return true;
}

bool solve(vector<vector<int>> board) {

	//채워진 칸 수, board 상태
	queue <vector<vector<int>>> q;
	q.push(board);

	while (!q.empty()) {
		vector<vector<int>> curBoard = q.front();
		q.pop();

		if (visited.find(curBoard) != visited.end()) return;
		visited.insert(curBoard);

		//base case
		if (finished(curBoard)) {
			for (int i = 0; i < 9; ++i) {
				for (int j = 0; j < 9; ++j) {
					cout << curBoard[i][j];
				}
				cout << "\n";
			}
			return;
		}

		bool solved = false;

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (curBoard[i][j] == 0) {
					for (int k = 1; k <= 9; ++k) {
						curBoard[i][j] = k;
						if (correct(curBoard) && visited.find(curBoard) == visited.end()){
							q.push(curBoard);
						}
					}
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	vector<vector<int>> board;

	for (int i = 0; i < 9; ++i) {
		string str;
		vector<int> v;

		cin >> str;
		
		for (int j = 0; j < 9; ++j) {
			v.push_back(str[j] - '0');
		}
		board.push_back(v);
	}

	solve(board);
	return 0;
}