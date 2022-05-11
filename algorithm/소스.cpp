#include <string>
#include <vector>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;

const int SIZE = 4;

int answer = 987654321;

int dirR[4] = { 0,0,1,-1};
int dirC[4] = { 1, -1, 0, 0 };

bool inRange(int r, int c) {
	if (r < 0 || r >= SIZE) return false;
	if (c < 0 || c >= SIZE) return false;
	return true;
}

bool boardEmpty(vector<vector<int>> board) {
	bool flag = true;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (board[i][j] != 0) {
				flag = false;
				break;
			}
		}
	}
	return flag;
}

struct state {
	vector<vector<int>> board;
	int curR;
	int curC; 
	
	state(vector<vector<int>> _board, int _curR, int _curC){
		for (int i = 0; i < SIZE; ++i) {
			board.push_back(_board[i]);
		}
		curR = _curR;
		curC = _curC;
	}

	bool operator<(const state& rhs) const{
		if (curR != rhs.curR) return curR < rhs.curR;
		if (curC != rhs.curC) return curC < rhs.curC;
		return board < rhs.board;
	}
};

map<state, int> cache;

void solve(int curR, int curC, vector<vector<int>> curBoard, int moveCnt) {
	
	//가지치기
	state curState = state(curBoard, curR, curC);

	if (cache.find(curState) == cache.end()) {
		cache[curState] = moveCnt;
	}
	else {
		if (cache[curState] < moveCnt) return;
		else cache[curState] = moveCnt;
	}

	//base case - 모든 카드 제거된 경우 종료
	if (boardEmpty(curBoard)) {
		answer = min(answer, moveCnt);
		return;
	}

	//현재 커서 카드 위에 있고 카드가 뒷면인 경우
	if (curBoard[curR][curC] != 0 && curBoard[curR][curC] < 10) {
		//앞면으로 뒤집기 (+10)
		curBoard[curR][curC] += 10;
		solve(curR, curC, curBoard, moveCnt + 1);
		curBoard[curR][curC] -= 10;

		//뒤집지 않는다
		//no action
	}

	//앞면인 카드가 두 개인 경우 카드 제거
	vector<pair<int, int>> card;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (curBoard[i][j] > 10) {
				card.push_back({ i, j });
			}
		}
	}
	if (card.size() == 2) {
		int r1 = card[0].first; int c1 = card[0].second;
		int r2 = card[1].first; int c2 = card[1].second;

		//카드 제거
		if (curBoard[r1][c1] == curBoard[r2][c2]) {
			curBoard[r1][c1] = curBoard[r2][c2] = 0;

			//base case - 모든 카드 제거된 경우 종료
			if (boardEmpty(curBoard)) {
				answer = min(answer, moveCnt);
				return;
			}
		}
		//도로 뒷면으로 뒤집기 (-10)
		else {
			curBoard[r1][c1] -= 10;
			curBoard[r2][c2] -= 10;
		}
	}
	
	//다음 칸으로 이동
	for (int d = 0; d < 4; ++d) {

		//다음 칸으로 이동할 수 있는지 나타냄
		bool flag = false;

		//방향키
		int nextR = curR + dirR[d];
		int nextC = curC + dirC[d];
		if (inRange(nextR, nextC)) {
			flag = true;

			//가지치기
			state nextState = state(curBoard, nextR, nextC);

			if (cache.find(nextState) == cache.end() || cache[nextState] > moveCnt) {
				solve(nextR, nextC, curBoard, moveCnt + 1);
			}
		}

		if (flag) {
			//ctrl + 빙향키
			nextR = curR + dirR[d];
			nextC = curC + dirC[d];

			while (inRange(nextR, nextC)) {
				if ((curBoard[nextR][nextC] != 0) || (!inRange(nextR + dirR[d], nextC + dirC[d]))) {
					
					//가지치기
					state nextState = state(curBoard, nextR, nextC);

					if (cache.find(nextState) == cache.end() || cache[nextState] > moveCnt) {
						solve(nextR, nextC, curBoard, moveCnt + 1);
					}
					break;
				}
				nextR += dirR[d];
				nextC += dirC[d];
			}
		}
	}
}


int solution(vector<vector<int>> board, int r, int c) {
	
	solve(r, c, board, 0);

	return answer;
}

int main() {
	solution({ {1, 0, 0, 3},{2, 0, 0, 0},{0, 0, 0, 2},{3, 0, 1, 0} },1,	0);
}


