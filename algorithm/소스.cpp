#include <iostream>
#include <cstring>
using namespace std;

int R, C;

//빈 칸 0, 고양이 칸 1
int mp[26][26];
int cache[26][26];

int validPath(int r, int c) {
	//base case
	//(R,C)에 도착한 경우 경로 하나 발견
	if (r == R && c == C) return 1;
	//범위 밖으로 간 경우 경로 X
	if (r < 1 || r > R) return 0;
	if (c < 1 || c > C) return 0;
	//고양이가 있는 칸인 경우 경로 X
	if (mp[r][c] == 1) return 0;

	int& ret = cache[r][c];
	if (ret != -1) return ret;

	//오른쪽으로 이동하는 경로 + 아래로 이동하는 경로
	ret = validPath(r + 1, c) + validPath(r, c + 1);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(mp, 0, sizeof(mp));
	memset(cache, -1, sizeof(cache));

	cin >> R >> C;
	int k;
	cin >> k;
	for (int i = 0; i < k; ++i) {
		int r, c;
		cin >> r >> c;
		mp[r][c] = 1;
	}

	cout << validPath(1, 1);

	return 0;
}