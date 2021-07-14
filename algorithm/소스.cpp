#include <iostream>
#include <queue>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

const int MAXN = 500;

int n;
int mp[MAXN + 1][MAXN + 1];
int isVisited[MAXN + 1][MAXN + 1];
//pair<pair<r, c>, dist>
queue <pair<pair<int, int>, int>> q;

int dirR[4] = { -1,0,0,1 };
int dirC[4] = { 0,-1,1,0 };

int bfs(int startR, int startC) {
	q.push(make_pair(make_pair(startR, startC), 1));

	int maxDist = 0;
	while (!q.empty()) {
		pair<pair<int, int>, int> cur = q.front();
		q.pop();

		int curR = cur.first.first;
		int curC = cur.first.second;
		int curDist = cur.second;

		if (isVisited[curR][curC])continue;
		isVisited[curR][curC] = true;

		maxDist = max(maxDist, curDist);

		for (int i = 0; i < 4; i++) {
			int nextR = curR + dirR[i];
			int nextC = curC + dirC[i];

			if (nextR < 1 || nextR > n) continue;
			if (nextC < 1 || nextC > n) continue;
			if (mp[curR][curC] >= mp[nextR][nextC]) continue;

			q.push(make_pair(make_pair(nextR, nextC), curDist + 1));
		}
	}
	return maxDist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> mp[i][j];

	int ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			memset(isVisited, 0, sizeof(isVisited));
			ans = max(ans, bfs(i, j));
		}

	cout << ans;
	return 0;
}