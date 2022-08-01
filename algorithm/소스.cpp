#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

typedef long long ll;

int L;
vector<string> board;

bool usedBLock[5] = { 0 };
vector<vector<string>> block(5, vector<string>());

set<string> visited;

string minAns;

bool inRange(int r, int c) {
	if (r < 0 || r >= L) return false;
	if (c < 0 || c >= L) return false;
	return true;
}

bool check(int startR, int startC, int blockNum) {
	for (int i = 0; i < block[blockNum].size(); ++i) {
		for (int j = 0; j < block[blockNum][i].size(); ++j) {
			if (!inRange(startR + i, startC + j)) return false;

			if ((block[blockNum][i][j] == '#') && (board[startR + i][startC + j] != '0')) {
				return false;
			}
		}
	}
	return true;
}

void fill(int startR, int startC, int blockNum) {
	for (int i = 0; i < block[blockNum].size(); ++i) {
		for (int j = 0; j < block[blockNum][i].size(); ++j) {
			if (block[blockNum][i][j] == '#')
				board[startR + i][startC + j] = (char)(blockNum + 1 + '0');
		}
	}
}

void empty(int startR, int startC, int blockNum) {
	for (int i = 0; i < block[blockNum].size(); ++i) {
		for (int j = 0; j < block[blockNum][i].size(); ++j) {
			if (block[blockNum][i][j] == '#')
				board[startR + i][startC + j] = '0';
		}
	}
}

bool solved() {
	//블럭 5개 모두 사용하지 않은 경우 답 X
	for (int i = 0; i < 5; ++i) {
		if (!usedBLock[i]) return false;
	}

	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < L; ++j) {
			if (board[i][j] == '0') return false;
		}
	}
	return true;
}


void solve() {
	string curBoard = "";
	for (int i = 0; i < L; ++i) {
		curBoard += board[i];
	}

	//base case
	if (solved()) {
		minAns = min(minAns, curBoard);
		return;
	}

	if (visited.find(curBoard) != visited.end()) return;
	visited.insert(curBoard);

	if (curBoard > minAns) return;

	for (int r = 0; r < L; ++r) {
		for (int c = 0; c < L; ++c) {
			if (board[r][c] == '0') {
				for (int blockNum = 0; blockNum < 5; ++blockNum) {
					if (usedBLock[blockNum]) continue;

					int startC;
					for (int i = 0; i < block[blockNum][0].size(); ++i) {
						if (block[blockNum][0][i] == '#') {
							startC = c - i;
							break;
						}
					}

					if (!check(r, startC, blockNum)) continue;

					usedBLock[blockNum] = true;
					fill(r, startC, blockNum);

					string nextBoard = "";
					for (int i = 0; i < L; ++i) {
						nextBoard += board[i];
					}

					if ((visited.find(nextBoard) == visited.end()) && (nextBoard < minAns))
						solve();

					usedBLock[blockNum] = false;
					empty(r, startC, blockNum);
				}
				break;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> L;

	//board 초기화
	for (int i = 0; i < L; ++i) {
		board.push_back("");
		for (int j = 0; j < L; ++j) {
			board[i] += '0';
		}
	}

	//minAns 초기화
	minAns = "";
	string noAns = "";
	for (int i = 0; i < (L*L); ++i) {
		minAns += '6';
		noAns += '6';
	}

	for (int i = 0; i < 5; ++i) {
		int n, m;
		cin >> n >> m;
		for (int j = 0; j < n; ++j) {
			string input;
			cin >> input;
			block[i].push_back(input);
		}
	}

	solve();

	if (minAns == noAns) cout << "gg";
	else {
		for (int i = 0; i < (L*L); i += L) {
			cout << minAns.substr(i, L) << "\n";
		}
	}

	return 0;
}