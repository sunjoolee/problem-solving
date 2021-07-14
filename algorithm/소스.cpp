#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
const int IMPOSSIBLE = 2000000;

int N, M;
string mp[MAXN + 5];
int cache[MAXN + 5][MAXN + 5][2];

int rdir[4] = { -1,0,0,1 };
int cdir[4] = { 0,-1,1,0 };

//state = 1: 벽을 한 번 부술 수 있는 상태
//state = 0: 벽을 더이상 부술 수 없는 상태 
int getMin(int r, int c, int state) {
	if (r == N && c == M) return 1;

	int& ret = cache[r][c][state];
	if (ret != -1) return ret;

	if (mp[r][c] == '1') {
		if (state == 1) state = 0;
		else return IMPOSSIBLE;
	}

	ret = IMPOSSIBLE;
	for (int i = 0; i < 4; ++i) {
		int nextr = r + rdir[i];
		int nextc = c + cdir[i];

		if (nextr < 1 || nextr > N) continue;
		if (nextc < 1 || nextc > M) continue;

		ret = min(ret, 1 + getMin(nextr, nextc, state));
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> N >> M;
	string input;
	for (int i = 1; i <= N; ++i) {
		cin >> input;
		mp[i] = "0" + input;
	}

	int dist = getMin(1, 1, 1);

	if (dist == IMPOSSIBLE) cout << -1;
	else cout << dist;
	return 0;
}

