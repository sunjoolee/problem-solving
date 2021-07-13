#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

// M : 0, O : 1, L : 2, A : 3, ±×¿Ü ¾ËÆÄºª: 4

int N;
int grnd[501][501];
int cache[501][501][5][5][5];

int cntMOLA(int r, int c, int prev3, int prev2, int prev1) {
	if (r < 1 || r > N) return 0;
	if (c < 1 || c > N) return 0;

	int& ret = cache[r][c][prev3][prev2][prev1];
	if (ret != -1) return ret;

	ret = 0;

	int now = grnd[r][c];
	if (prev3 == 0 && prev2 == 1 && prev1 == 2 && now == 3) ++ret;

	ret += max(cntMOLA(r, c + 1, prev2, prev1, now), cntMOLA(r + 1, c, prev2, prev1, now));
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> N;
	char input;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			cin >> input;
			if (input == 'M') grnd[i][j] = 0;
			else if (input == 'O') grnd[i][j] = 1;
			else if (input == 'L') grnd[i][j] = 2;
			else if (input == 'A') grnd[i][j] = 3;
			else grnd[i][j] = 4;
		}

	cout << cntMOLA(1, 1, 4, 4, 4);

	return 0;
}