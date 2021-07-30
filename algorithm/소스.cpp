#include <iostream>
#include <cstring>
#include <limits.h>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const int MAXN = 2223;

int n;
int mp[MAXN][MAXN];
ull cache[MAXN][MAXN];

int dirr[2] = { 0,1 };
int dirc[2] = { 1,0 };

//dp(r,c): (r,c)��ǥ���� (n-1,n-1)��ǥ���� ���µ� �ʿ��� �ּ� ���
ull dp(int r, int c) {
	//base case
	if (r == n - 1 && c == n - 1) return 0;

	ull& ret = cache[r][c];
	if (ret != -1) return ret;

	ret = LLONG_MAX;
	for (int i = 0; i < 2; i++) {
		int nextr = r + dirr[i];
		int nextc = c + dirc[i];

		if (r < 0 || r >= n) continue;
		if (c < 0 || c >= n) continue;

		//���� ĭ�� ���� ĭ���� ũ�ų� ���� ��� ��� �߻�
		if (mp[r][c] <= mp[nextr][nextc]) {
			ret = min(ret, (mp[nextr][nextc] - mp[r][c] + 1) + dp(nextr, nextc));
		}
		else
			ret = min(ret, dp(nextr, nextc));
	}
	
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < MAXN; ++i)
		for (int j = 0; j < MAXN; ++j)
			cache[i][j] = -1;

	cin >> n;
	for (int i = 0; i < n; ++i)
		for(int j = 0; j<n; ++j)
			cin >> mp[i][j];

	cout<< dp(0, 0);
	return 0;
}