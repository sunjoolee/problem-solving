#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXX = 50;

int w, h;
int mp[MAXX + 1][MAXX + 1] = { 0 };
int visited[MAXX + 1][MAXX + 1] = { 0 };

int dirr[8] = { -1,-1,-1,0,0,1,1,1 };
int dirc[8] = { -1,0,1,-1,1,-1,0,1 };

//mp[r][c]와 이어진 섬을 방문한다
void bfs(int r, int c) {
	queue<pair<int, int>> q;
	q.push(make_pair(r, c));

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		int curr = cur.first;
		int curc = cur.second;
		q.pop();

		//방문 확인
		if (visited[curr][curc]) continue;
		visited[curr][curc] = 1;
		
		for (int i = 0; i < 8; i++) {
			int nextr = curr + dirr[i];
			int nextc = curc + dirc[i];
			
			//범위 확인
			if (nextr < 0 || nextr >= h) continue;
			if (nextc < 0 || nextc >= w) continue;

			//현재 섬과 이어진 섬 방문
			if (mp[nextr][nextc] == 1) 
				q.push(make_pair(nextr, nextc));
		}
	}

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true) {
		memset(visited, 0, sizeof(visited));

		cin >> w >> h;
		if (w == 0 && h == 0) break;

		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				cin >> mp[i][j];

		int cnt = 0;
		for (int r = 0; r < h; ++r)
			for (int c = 0; c < w; ++c)
				if (mp[r][c] == 1 && visited[r][c] == 0) {
					bfs(r, c);
					++cnt;
				}
		cout << cnt << "\n";
	}
	
	return 0;
}