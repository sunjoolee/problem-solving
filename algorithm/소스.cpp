#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m, k;
int map[51][51];
int found[51][51];

int dirR[4] = { 0,0,1,-1 };
int dirC[4] = { 1,-1,0,0 };

void dfs(int startR, int startC) {
	queue<pair<int, int>> q;

	found[startR][startC] = 1;
	q.push({startR, startC});

	while (!q.empty()) {
		pair<int, int> here = q.front();
		int hereR = here.first;
		int hereC = here.second;
		q.pop();

		for(int i = 0; i < 4; ++i) {
			int nextR = hereR + dirR[i];
			int nextC = hereC + dirC[i];

			if (nextR < 0 || nextR >= n) continue;
			if (nextC < 0 || nextC >= m) continue;

			if (map[nextR][nextC] == 1 && found[nextR][nextC] == 0) {
				found[nextR][nextC] = 1;
				q.push({ nextR, nextC });
			}
		}

	}

}

int solve() {
	int cnt = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map[i][j] == 1 && found[i][j] == 0) {
				cnt++;
				dfs(i, j);
			}
		}
	}

	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;

	while (t--) {
		//√ ±‚»≠
		for (int i = 0; i <= 50; ++i) {
			memset(map[i], 0, sizeof(map[i]));
			memset(found[i], 0, sizeof(found[i]));
		}

		cin >> n >> m >> k;

		for (int i = 0; i < k; ++i) {
			int x, y;
			cin >> x >> y;
			map[x][y] = 1;
		}

		cout << solve()<<"\n";
	}

	return 0;
}