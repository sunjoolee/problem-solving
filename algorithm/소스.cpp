#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAX_N = 25;
const int INF = 987654321;

int N;

//���� 0, 1, 2, 3
int dirR[4] = { 1, -1, 0, 0 };
int dirW[4] = { 0, 0, 1, -1 };

bool inRange(int r, int w) {
	if (r < 0 || r >= N) return false;
	if (w < 0 || w >= N) return false;
	return true;
}

//curR, curW, prevDir
typedef pair<pair<int, int>, int> pos;

int solution(vector<vector<int>> board) {
	N = board.size();

	queue<pair<pos, int>> q;
	q.push({ {{0, 0}, 0 }, 0 });

	map <pos, int> visitedCost;
	visitedCost[{ {0, 0}, 0 }] = 0;

	while (!q.empty()) {

		pos curPos = q.front().first;
		int curCost = q.front().second;
		q.pop();

		//�̹� �湮�� ��ǥ�� ���, �ִ� ������� Ȯ��
		if (visitedCost.find(curPos) != visitedCost.end()) {
			if (visitedCost[curPos] < curCost)
				continue;
		}
		visitedCost[curPos] = curCost;


		//���� ��ġ���� �̵� ������ ���� Ȯ��
		int curR = curPos.first.first;
		int curW = curPos.first.second;
		int prevDir = curPos.second;

		for (int dir = 0; dir < 4; ++dir) {
			int nextR = curR + dirR[dir];
			int nextW = curW + dirW[dir];

			if (inRange(nextR, nextW) == false || board[nextR][nextW] == 1) continue;

			pos nextPos = { {nextR, nextW}, dir };
			int nextCost;

			//�� ����� �� ������ ��ġ�ϴ��� Ȯ��
			//���� ��ġ (0,0)�� ��� �� ���� üũ X
			if ((dir == prevDir) || (curR == 0 && curW == 0))
				nextCost = 100 + curCost;
			else
				nextCost = 600 + curCost;

			//�̹� �湮�� ��ǥ�� ���, �ִ� ������� Ȯ��
			if (visitedCost.find(nextPos) != visitedCost.end()) {
				if (visitedCost[nextPos] < nextCost) 
					continue;
			}
			q.push({ nextPos, nextCost });
			visitedCost[nextPos] = nextCost;
		}
	}

	int res = INF;
	if (visitedCost.find({ {N - 1, N - 1}, 0 }) != visitedCost.end())
		res = min(res, visitedCost[{ {N - 1, N - 1}, 0}]);
	if (visitedCost.find({ {N - 1, N - 1}, 1 }) != visitedCost.end())
		res = min(res, visitedCost[{ {N - 1, N - 1}, 1}]);
	if (visitedCost.find({ {N - 1, N - 1}, 2 }) != visitedCost.end())
		res = min(res, visitedCost[{ {N - 1, N - 1}, 2}]);

	return res;
}

