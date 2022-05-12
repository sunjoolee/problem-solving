#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

bool correct(vector<vector<int>> board) {
	
	for (int i = 0; i < 9; ++i) {
		//�� �࿡ ���� ���� �ߺ����� �ʴ��� Ȯ��
		string maskRow = "000000000";

		//�� ���� ���� ���� �ߺ����� �ʴ��� Ȯ��	
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

	//�� ĭ�� ���� ���� �ߺ����� �ʴ��� Ȯ��
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


set<vector<vector<int>>> visited;

void dfs(vector<vector<int>> curBoard) {

	if (finished(curBoard)) {
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				cout << curBoard[i][j];
			}
			cout << "\n";
		}

		exit(0);
	}

	if (visited.find(curBoard) != visited.end()) 
		return;
	visited.insert(curBoard);

	bool change = false;
	for (int i = 0; i < 9; ++i) {
		if (change) return;
		for (int j = 0; j < 9; ++j) {
			if (change) return;

			if (curBoard[i][j] == 0) {
				for (int k = 0; k < 9; ++k) {
					curBoard[i][j] = k;
					if (correct(curBoard)) {
						dfs(curBoard);
					}
				}
				change = true;
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

	dfs(board);

	return 0;
}