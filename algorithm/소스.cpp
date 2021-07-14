#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
const int IMPOSSIBLE = 2000000;

int N, M;
string mp[MAXN + 2];
bool isVisited[MAXN + 2][MAXN + 2][2] = { 0 };
queue<pair<pair<int, int>, pair<int,int>>> que;
//pair<pair<r, c>, pair<state, dist> 
int dirR[4] = {-1,0,0,1};
int dirC[4] = {0,-1,1,0};


int bfs() {
	//(1,1)
	que.push(make_pair(make_pair(1, 1), make_pair(1, 1)));

	int minDist = IMPOSSIBLE;
	while (!que.empty()) {
		pair<pair<int, int>, pair<int, int>> cur = que.front();
		que.pop();

		int curR = cur.first.first;
		int curC = cur.first.second;
		int curState = cur.second.first;
		int curDist = cur.second.second;

		
		if (isVisited[curR][curC][curState]) 
			continue; 
		isVisited[curR][curC][curState] = true;

		//end
		if (curR == N && curC == M) {
			minDist = min(minDist, curDist);
			continue;
		}
		
	
		if (mp[curR][curC] == '1') {
			if (curState == 1) curState = 0;
			else continue;
		}

		//to next
		for (int i = 0; i < 4; i++) {
			int nextR = curR + dirR[i];
			int nextC = curC + dirC[i];

			if (nextR < 1 || nextR > N) continue;
			if (nextC < 1 || nextC > M) continue;

			que.push(make_pair(make_pair(nextR, nextC), make_pair(curState, curDist + 1)));
		}
	}

	if (minDist == IMPOSSIBLE) return -1;
	return minDist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		string input;
		cin >> input;
		mp[i] = "0" + input;
	}
	
	cout << bfs();
	return 0;
}