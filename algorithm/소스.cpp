#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

bool correct(vector<vector<int>> board) {
	
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
	for (int i = 0; i < 3; ++i) {
		string mask = "000000000";
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] != 0) {
				if (mask[board[i][j] - 1] != '0') return false;
				mask[board[i][j] - 1] = '1';
			}
		}

		mask = "000000000";
		for (int j = 3; j < 6; ++j) {
			if (board[i][j] != 0) {
				if (mask[board[i][j] - 1] != '0') return false;
				mask[board[i][j] - 1] = '1';
			}
		}

		mask = "000000000"; 
		for (int j = 6; j < 9; ++j) {
			if (board[i][j] != 0) {
				if (mask[board[i][j] - 1] != '0') return false;
				mask[board[i][j] - 1] = '1';
			}
		}
	}
	for (int i = 3; i < 6; ++i) {
		string mask = "000000000";
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] != 0) {
				if (mask[board[i][j] - 1] != '0') return false;
				mask[board[i][j] - 1] = '1';
			}
		}

		mask = "000000000";
		for (int j = 3; j < 6; ++j) {
			if (board[i][j] != 0) {
				if (mask[board[i][j] - 1] != '0') return false;
				mask[board[i][j] - 1] = '1';
			}
		}

		mask = "000000000";
		for (int j = 6; j < 9; ++j) {
			if (board[i][j] != 0) {
				if (mask[board[i][j] - 1] != '0') return false;
				mask[board[i][j] - 1] = '1';
			}
		}
	}
	for (int i = 6; i < 9; ++i) {
		string mask = "000000000";
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] != 0) {
				if (mask[board[i][j] - 1] != '0') return false;
				mask[board[i][j] - 1] = '1';
			}
		}

		mask = "000000000";
		for (int j = 3; j < 6; ++j) {
			if (board[i][j] != 0) {
				if (mask[board[i][j] - 1] != '0') return false;
				mask[board[i][j] - 1] = '1';
			}
		}

		mask = "000000000";
		for (int j = 6; j < 9; ++j) {
			if (board[i][j] != 0) {
				if (mask[board[i][j] - 1] != '0') return false;
				mask[board[i][j] - 1] = '1';
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

vector<vector<int>> bfs(vector<vector<int>> board) {

	queue <vector<vector<int>>> q;
	q.push(board);

	set<vector<vector<int>>> visited;

	while (!q.empty()) {
		vector< vector<int>> curBoard = q.front();
		q.pop();

		if (finished(curBoard))
			return curBoard;

		if (visited.find(curBoard) != visited.end()) continue;
		visited.insert(curBoard);

		bool change = false;
		for (int i = 0; i < 9; ++i) {
			if (change) break;
			for (int j = 0; j < 9; ++j) {
				if (change) break;

				if (curBoard[i][j] == 0) {
					for (int k = 0; k < 9; ++k) {
						curBoard[i][j] = k;
						if (correct(curBoard)) {
							q.push(curBoard);
						}
					}
					change = true;
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

	vector<vector<int>> answer = bfs(board);
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			cout << answer[i][j];
		}
		cout << "\n";
	}

	return 0;
}