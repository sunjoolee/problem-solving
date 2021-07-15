#include <iostream>
#include <queue>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

const int MAXN = 500;

int n;
int cache[MAXN + 1][MAXN + 1];
int mp[MAXN + 1][MAXN + 1];

int dirR[4] = { -1,0,0,1 };
int dirC[4] = { 0,-1,1,0 };

int dp(int r, int c) {
	int& ret = cache[r][c];
	if (ret != -1) return ret;

	ret = 1;
	for (int i = 0; i < 4; i++) {
		int nextR = r + dirR[i];
		int nextC = c + dirC[i];

		if (nextR < 1 || nextR > n) continue;
		if (nextC < 1 || nextC > n) continue;
		if (mp[r][c] < mp[nextR][nextC])
			ret = max(ret,1 + dp(nextR, nextC));
		
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> mp[i][j];

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			dp(i,j);

	int ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			ans = max(ans, cache[i][j]);

	cout << ans;
	return 0;
}