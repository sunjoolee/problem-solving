#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int w, h;
//지도(1: 땅, 0: 바다)
int map[51][51];
//그래프 정점 V: 지도의 땅의 좌표
vector<pair<int, int>> V;
//그래프 정점 방문 표시
bool visited[51][51] = { 0 };

int dirR[8] = {-1,-1,-1,0,0,1,1,1};
int dirC[8] = {-1,0,1,-1,1,-1,0,1};

void dfs(int row, int col) {
	visited[row][col] = true;

	for (int i = 0; i < 8; ++i) {
		int row2 = row + dirR[i];
		int col2 = col + dirC[i];

		if (row2 < 0 || row2 >= h) continue;
		if (col2 < 0 || col2 >= w) continue;

		if (map[row2][col2] && !visited[row2][col2])
			dfs(row2,col2);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true) {
		//초기화
		V.clear();
		for (int i = 0; i < 50; ++i) {
			for (int j = 0; j < 50; ++j) {
				map[i][j] = -1;
				visited[i][j] = false;
			}
		}

		cin >> w >> h;
		if (!w && !h) break;

		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				cin >> map[i][j];

				if (map[i][j]) V.push_back({ i, j });
			}
		}

		int cnt = 0;
		for (int i = 0; i < V.size(); ++i) {
			int row = V[i].first;
			int col = V[i].second;
			if (map[row][col] && !visited[row][col]) {
				dfs(row, col);
				cnt++;
			}
		}
		cout << cnt << "\n";
	}
	return 0;
}