#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N;

struct qNode {
	int cost;
	//로봇의 위치 좌측상단 좌표로 판단
	int r;
	int w;
	//로봇 가로 방향 0/세로 방향 1
	int dir;

	bool operator<(const qNode node) const {
		return this->cost > node.cost;
	}
};

bool inRange(int r, int w) {
	if (r < 0 || r >= N) return false;
	if (w < 0 || w >= N) return false;
	return true;
}


int solution(vector<vector<int>> board) {
	N = board.size();
	int answer =0;

	//BFS
	//(0,0),(0,1) 에서 시작

	vector<vector<vector<int>>> visited(N, vector<vector<int>> (N, vector<int>(2, 0)));
	priority_queue<qNode> q;
	q.push({ 0, 0, 0, 0 });

	while (!q.empty()) {
		int curCost = q.top().cost;
		int curR = q.top().r;
		int curW = q.top().w;
		int curDir = q.top().dir;
		q.pop();

		//종점인지 확인
		//가로
		if (curDir == 0){
			if (curR == N - 1 && curW == N - 2) {
				answer = -curCost;
				break;
			}
		}
		//세로
		else if (curR == N - 2 && curW == N - 1){
			answer = -curCost;
			break;
		}

		//이미 방문한 노드
		if (visited[curR][curW][curDir] == 1) continue;
		visited[curR][curW][curDir] = 1;

		//다음 노드 방문
		//가로
		if (curDir == 0) {
			//좌로 이동
			if (inRange(curR, curW - 1) && !board[curR][curW-1] && !visited[curR][curW - 1][0]){
				q.push({ curCost -1, curR, curW - 1, 0});
			}
			//우로 이동
			if (inRange(curR, curW + 2) && !board[curR][curW +2] && !visited[curR][curW + 2][0]) {
				q.push({ curCost - 1, curR, curW + 1, 0});
			}
			//위로 회전
			if (inRange(curR - 1, curW ) && inRange(curR - 1, curW + 1) && !board[curR-1][curW] && !board[curR-1][curW + 1]){
				if(!visited[curR-1][curW + 1][1]) 
					q.push({ curR - 1, curW + 1, 1, curCost + 1 });
				if (!visited[curR - 1][curW][1])
					q.push({ curCost - 1, curR - 1, curW, 1});
			}
			//아래로 회전
			if (inRange(curR + 1, curW) && inRange(curR + 1, curW + 1) && !board[curR + 1][curW] && !board[curR + 1][curW + 1]) {
				if (!visited[curR + 1][curW + 1][1])
					q.push({ curCost - 1, curR + 1, curW + 1, 1 });
				if (!visited[curR + 1][curW][1])
					q.push({ curCost - 1, curR + 1, curW, 1});
			}
		}
		//세로
		else {
			//위로 이동
			if (inRange(curR - 1, curW) && !board[curR - 1][curW] &&!visited[curR - 1][curW][1]) {
				q.push({ curCost - 1, curR - 1, curW, 1});
			}
			//아래로 이동
			if (inRange(curR + 2, curW) && !board[curR + 2][curW ] && !visited[curR + 2][curW][0]) {
				q.push({ curCost - 1, curR + 2, curW, 1});
			}
			//좌로 회전
			if (inRange(curR, curW-1) && inRange(curR - 1, curW -1) && !board[curR][curW - 1] && !board[curR-1][curW - 1]) {
				if (!visited[curR][curW - 1][0])
					q.push({ curCost - 1, curR, curW - 1, 0});
				if (!visited[curR - 1][curW - 1][0])
					q.push({ curCost - 1, curR - 1, curW - 1, 0});
			}
			//우로 회전
			if (inRange(curR, curW + 1) && inRange(curR - 1, curW + 1)&& !board[curR][curW + 1] && !board[curR-1][curW + 1]) {
				if (!visited[curR][curW ][0])
					q.push({ curCost - 1, curR , curW , 0 });
				if (!visited[curR - 1][curW][0])
					q.push({ curCost - 1, curR - 1, curW, 0});
			}
		}
	}


	return answer;
}

int main() {
	solution({ {0, 0, 0, 0, 0, 0, 1},{1, 1, 1, 1, 0, 0, 1},{0, 0, 0, 0, 0, 0, 0},{0, 0, 1, 1, 1, 1, 0},{0, 1, 1, 1, 1, 1, 0},{0, 0, 0, 0, 0, 1, 1},{0, 0, 1, 0, 0, 0, 0} });
}