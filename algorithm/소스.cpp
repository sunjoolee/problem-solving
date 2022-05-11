#include <string>
#include <vector>
#include <queue>
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
	int r;
	int c; 
	vector<vector<int>> board;
	
	bool operator<(const state& rhs) const {
		if (r != rhs.r) return r < rhs.r;
		if (c != rhs.c) return c < rhs.c;
		return board < rhs.board;
	}
};


void bfs(int startR, int startC, vector<vector<int>> board) {
	queue<pair<state, int>> q;
	map<state, int> visited;

	q.push({ {startR, startC, board }, 0});

	while (!q.empty()) {
		state curState = q.front().first;
		int curMove = q.front().second;
		q.pop();

		if (visited.find(curState) != visited.end() && visited[curState] <= curMove) continue;
		visited[curState] = curMove;
		
		
		
		//ī�带 ������ �ʴ� ���

		vector<vector<int>> curBoard = curState.board;
		int curR = curState.r; 
		int curC = curState.c;

		//base case 
		if (boardEmpty(curBoard)) {
			answer = min(answer, curMove);
			return;
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

				state nextState = { nextR, nextC, curBoard };
				int nextMove = curMove + 1;
				if (visited.find(nextState) == visited.end() || visited[nextState] > nextMove) {
					q.push({ nextState,  nextMove });
				}
			}

			if (flag) {
				//ctrl + ����Ű
				nextR = curR + dirR[d];
				nextC = curC + dirC[d];

				while (inRange(nextR, nextC)) {
					if ((curBoard[nextR][nextC] != 0) || (!inRange(nextR + dirR[d], nextC + dirC[d]))) {

						state nextState = { nextR, nextC, curBoard };
						int nextMove = curMove + 1;

						if (visited.find(nextState) == visited.end() || visited[nextState] > nextMove) {
							q.push({ nextState,  nextMove });
						}
						break;
					}
					nextR += dirR[d];
					nextC += dirC[d];
				}
			}
		}

		//ī�带 ������ ���
		//���� Ŀ�� ī�� ���� �ְ� ī�尡 �޸��̾�� ��
		if (curBoard[curR][curC] == 0 || curBoard[curR][curC] > 10)
			continue;
		
		//�ո����� ������ (+10)
		curBoard[curR][curC] += 10;
		curMove++;

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
				curBoard[r1][c1] = 0;
				curBoard[r2][c2] = 0;
			}
			//���� �޸����� ������ (-10)
			else {
				curBoard[r1][c1] -= 10;
				curBoard[r2][c2] -= 10;
			}
		}

		//base case 
		if (boardEmpty(curBoard)) {
			answer = min(answer, curMove);
			return;
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

				state nextState = {nextR, nextC, curBoard};
				int nextMove = curMove + 2;
				if (visited.find(nextState) == visited.end() || visited[nextState] > nextMove) {
					q.push({ nextState,  nextMove });
				}
			}

			if (flag) {
				//ctrl + ����Ű
				nextR = curR + dirR[d];
				nextC = curC + dirC[d];

				while (inRange(nextR, nextC)) {
					if ((curBoard[nextR][nextC] != 0) || (!inRange(nextR + dirR[d], nextC + dirC[d]))) {

						state nextState = { nextR, nextC, curBoard };
						int nextMove = curMove + 2;
				
						if (visited.find(nextState) == visited.end() || visited[nextState] > nextMove) {
							q.push({ nextState,  nextMove });
						}
						break;
					}
					nextR += dirR[d];
					nextC += dirC[d];
				}
			}
		}
	}

	return;
}

int solution(vector<vector<int>> board, int r, int c) {
	bfs(r, c, board);
	return answer - 1;
}

int main() {
	solution({ {1, 0, 0, 3},{2, 0, 0, 0},{0, 0, 0, 2},{3, 0, 1, 0} },1,	0);
}


