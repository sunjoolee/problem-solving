#include <iostream>
#include <queue>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

const int MAXSIZE = 500;

int n,m;
//cache[r][c]: (r,c)의 좌표에서 시작하여 (n,m)까지 갈 수 있는 내리막길 수
int cache[MAXSIZE + 1][MAXSIZE + 1];
int mp[MAXSIZE + 1][MAXSIZE + 1];

int dirR[4] = { -1,0,0,1 };
int dirC[4] = { 0,-1,1,0 };

int dp(int r, int c) {
	if (r == n && c == m) return 1;

	int& ret = cache[r][c];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < 4; i++) {
		int nextR = r + dirR[i];
		int nextC = c + dirC[i];

		if (nextR < 1 || nextR > n) continue;
		if (nextC < 1 || nextC > m) continue;
		if (mp[r][c] > mp[nextR][nextC])
			ret += dp(nextR, nextC);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> mp[i][j];

	cout << dp(1, 1);
	return 0;
}