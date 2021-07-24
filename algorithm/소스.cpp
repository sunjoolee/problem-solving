#include <iostream>
#include <algorithm>
using namespace std;

int dp[1002][1002] = { 0 };

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	while (true) {
		cin >> n >> m;
		if (n == 0 && m == 0)
			break;

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				cin >> dp[i][j];

		int res = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				if (dp[i][j] == 0) continue;

				dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]), dp[i][j-1]) + 1;
				res = max(res, dp[i][j]);
			}
		cout << res << "\n";
	}

	return 0;
}