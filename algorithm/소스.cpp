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
	
	//����ġ��
	state curState = state(curBoard, curR, curC);

	if (cache.find(curState) == cache.end()) {
		cache[curState] = moveCnt;
	}
	else {
		if (cache[curState] < moveCnt) return;
		else cache[curState] = moveCnt;
	}

	//base case - ��� ī�� ���ŵ� ��� ����
	if (boardEmpty(curBoard)) {
		answer = min(answer, moveCnt);
		return;
	}

	//���� Ŀ�� ī�� ���� �ְ� ī�尡 �޸��� ���
	if (curBoard[curR][curC] != 0 && curBoard[curR][curC] < 10) {
		//�ո����� ������ (+10)
		curBoard[curR][curC] += 10;
		solve(curR, curC, curBoard, moveCnt + 1);
		curBoard[curR][curC] -= 10;

		//������ �ʴ´�
		//no action
	}

	//�ո��� ī�尡 �� ���� ��� ī�� ����
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

		//ī�� ����
		if (curBoard[r1][c1] == curBoard[r2][c2]) {
			curBoard[r1][c1] = curBoard[r2][c2] = 0;

			//base case - ��� ī�� ���ŵ� ��� ����
			if (boardEmpty(curBoard)) {
				answer = min(answer, moveCnt);
				return;
			}
		}
		//���� �޸����� ������ (-10)
		else {
			curBoard[r1][c1] -= 10;
			curBoard[r2][c2] -= 10;
		}
	}
	
	//���� ĭ���� �̵�
	for (int d = 0; d < 4; ++d) {

		//���� ĭ���� �̵��� �� �ִ��� ��Ÿ��
		bool flag = false;

		//����Ű
		int nextR = curR + dirR[d];
		int nextC = curC + dirC[d];
		if (inRange(nextR, nextC)) {
			flag = true;

			//����ġ��
			state nextState = state(curBoard, nextR, nextC);

			if (cache.find(nextState) == cache.end() || cache[nextState] > moveCnt) {
				solve(nextR, nextC, curBoard, moveCnt + 1);
			}
		}

		if (flag) {
			//ctrl + ����Ű
			nextR = curR + dirR[d];
			nextC = curC + dirC[d];

			while (inRange(nextR, nextC)) {
				if ((curBoard[nextR][nextC] != 0) || (!inRange(nextR + dirR[d], nextC + dirC[d]))) {
					
					//����ġ��
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


