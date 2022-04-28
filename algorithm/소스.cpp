#include <string>
#include <vector>
#include <queue>
#include <map>\
#include <math.h>
#include <algorithm>

using namespace std;

const string emptyBoard = "0000000000000000";

int dirR[4] = { 0, 0, 1, -1 };
int dirC[4] = { 1, -1, 0, 0 };

struct qNode {
	int r;
	int c;
	int moves;
	string board;
	pair<int, int> select;
};

struct mapNode {
	int r, c;
	string board;

	bool operator ==(const mapNode &var) const {
		if (r == var.r && c == var.c && board == var.board) return true;
		return false;
	}

	bool operator <(const mapNode &var) const{
		if (r < var.r) return true;
		if (r > var.r) return false;

		if (c < var.c) return true;
		if (c > var.c) return false;

		return board < var.board;
	}
};

//(r, c) -> (i, j) 이동 최소 조작 횟수
int getMoves(int r, int c, int i, int j) {
	if (r == i && c == j) return 0;
	else if (r == i || c == j) return 1;
	else if (i == 0 || i == 3 || j == 0 || j == 3) return 2;
	return min(abs(r - i), abs(c - j)) + 1;
}

bool inRange(int i, int j) {
	if (0 > i || i >= 4) return false;
	if (0 > j || j >= 4) return false;
	return true;
}

int BFS(string board, int r, int c) {
	map <mapNode, int> visited;
	queue<qNode> q;

	q.push({ r, c, 0, board, {-1, -1}});

	int answer = 987654321;

	while (!q.empty()) {
		int r = q.front().r;
		int c = q.front().c;
		int moves = q.front().moves;
		string curBoard= q.front().board;
		pair<int, int> select = q.front().select;
		q.pop();

		if (visited.find({ r, c, curBoard }) != visited.end()) {
			if (visited[{ r, c, curBoard }] < moves) continue;
		}
		visited[{r, c, curBoard}] = moves;

		if (curBoard == emptyBoard) {
			answer = min(answer, moves);
			continue;
		}
		
		//현재 좌표 카드인 경우 현재 좌표 선택
		if (curBoard[(4 * r) + c] != '0') {
			if (select.first == -1) {
				q.push({ r, c, moves +1, curBoard, {r, c} });
			}
			else {
				if (r == select.first && c == select.second) continue;

				if (curBoard[(4 * r) + c] == curBoard[(4 * select.first) + select.second]) {
					char tmp = curBoard[(4 * r) + c];
					curBoard[(4 * r) + c] = curBoard[(4 * select.first) + select.second] = '0';
					q.push({ r,c, moves + 1, curBoard, {-1, -1} });
					curBoard[(4 * r) + c] = curBoard[(4 * select.first) + select.second] = tmp;
				}
			}
		}

		//다음으로 이동할 좌표
		//방향키
		for (int i = 0; i < 4; ++i) {
			int nextR = r + dirR[i];
			int nextC = c + dirC[i];
			if (!inRange(nextR, nextC)) continue;
			

			//다음 좌표 카드이든 아니든 다음 좌표로 이동
			if (visited.find({ nextR, nextC, curBoard }) != visited.end()) {
				if (visited[{nextR, nextC, curBoard }] > moves + getMoves(r, c, nextR, nextC)) {
					q.push({ nextR, nextC, moves + getMoves(r, c, nextR, nextC), curBoard, {-1, -1} });
				}
			}

			//다음 좌표 카드인 경우
			if (curBoard[(4 * nextR) + nextC] != '0') {

				//다음 좌표로 이동 후 카드 선택
				//처음 선택하는 경우
				if (select.first == -1) {
					q.push({ nextR, nextC, moves + getMoves(r, c, nextR, nextC) + 1, curBoard, {nextR, nextC} });
				}

				//두번째로 선택하는 경우
				else {
					if (curBoard[(4 * nextR) + nextC] == curBoard[(4 * select.first) + select.second]) {
						char tmp = curBoard[(4 * nextR) + nextC];
						curBoard[(4 * nextR) + nextC] = curBoard[(4 * select.first) + select.second] = '0';
						q.push({ nextR, nextC, moves + getMoves(r, c, nextR, nextC) + 1, curBoard, {-1, -1} });
						curBoard[(4 * nextR) + nextC] = curBoard[(4 * select.first) + select.second] = tmp;
					}
				}
			}
		}

		//Ctrl + 방향키
		for (int i = 0; i < 4; ++i) {
			int nextR = r + dirR[i];
			int nextC = c + dirC[i];
			if (!inRange(nextR, nextC))continue;

			while (true) {
				//다음 좌표 카드아닌 경우 계속 이동
				if (curBoard[(4 * nextR) + nextC] == '0') continue;
				//다음 좌표 카드인 경우 이동 멈춤
				if (curBoard[(4 * nextR) + nextC] != '0') break;

				nextR += dirR[i];
				nextC += c + dirC[i];
			}
		}

	}
	
	return answer;
}

int solution(vector<vector<int>> board, int r, int c) {

	string boardStr = "";
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			boardStr += to_string(board[i][j]);
		}
	}

	int answer = BFS(boardStr, r, c);
	return answer;
}

int main() {
	solution({ {1, 0, 0, 3},{2, 0, 0, 0},{0, 0, 0, 2},{3, 0, 1, 0} }, 1, 0);
}