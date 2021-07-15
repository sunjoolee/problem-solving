#include <iostream>
#include <queue>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const int MAXSIZE = 100;

int n;
//cache[r][c]: (r,c)�� ��ǥ���� �����Ͽ� (n,n)���� �� �� �ִ� ����� ��
ull cache[MAXSIZE + 1][MAXSIZE + 1];
int mp[MAXSIZE + 1][MAXSIZE + 1];

ull dp(int r, int c) {
	if (r == n && c == n) return 1;

	ull& ret = cache[r][c];
	if (ret != -1) return ret;

	ret = 0;
	//���������� ����
	if (c + mp[r][c] <= n)
		ret += dp(r, c + mp[r][c]);
	//�Ʒ��� ����
	if (r + mp[r][c] <= n)
		ret += dp(r + mp[r][c],c);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> n ;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> mp[i][j];

	cout << dp(1, 1);
	return 0;
}