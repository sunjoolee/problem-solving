#include <iostream>
#include <queue>
#include <utility>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXX = 500;

int n,m;

int mp[MAXX + 1][MAXX + 1] = { 0 };
int visited[MAXX + 1][MAXX + 1] = { 0 };

int rdir[4] = {-1,0,0,1};
int cdir[4] = { 0,-1,1,0};

int bfs(int r, int c) {

	queue<pair<int,int>> que;

	int size = 1;
	que.push(make_pair(r,c));
	
	while (!que.empty()) {
		pair<int, int> cur = que.front();
		int curr = cur.first;
		int curc = cur.second;
		que.pop();

		if (visited[curr][curc]) continue;
		visited[curr][curc] = 1;
		++size;

		for (int i = 0; i < 4; i++) {
			int nextr = curr + rdir[i];
			int nextc = curc + cdir[i];

			if (nextr < 0 || nextr >= n) continue;
			if (nextc < 0 || nextc >= m) continue;

			if (mp[nextr][nextc] == 1 && visited[nextr][nextc] == 0) {
				que.push(make_pair(nextr, nextc));
			}
		}
	}
	return size;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		for(int j = 0; j<m; ++j)
			cin >> mp[i][j];

	int cnt = 0;
	int maxSize = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (mp[i][j] == 1 && visited[i][j] == 0) {
				cnt++;
				maxSize = max(maxSize, bfs(i, j));
			}

	cout << cnt << "\n" << maxSize;
	return 0;
}