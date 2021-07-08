#include<iostream>
#include<cstring>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
int N;
int cache[101][10][3][3];

int getCnt(int len, int num, int add, int sub) {
	//base case
	if (add >= 3 || sub >= 3) return 0;
	if (num < 0 || num > 9) return 0;
	if (len == N) return 1;

	int&ret = cache[len][num][add][sub];
	if (ret != -1) return ret;

	return ret = (getCnt(len + 1, num + 1, add + 1, 0) + getCnt(len + 1, num - 1, 0, sub + 1)) % MOD;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> N;

	int cnt = 0;

	//변형 계단 수는 0으로 시작할 수 있음
	for (int num = 0; num <= 9; num++)
		cnt = (cnt + getCnt(1, num, 0, 0)) % MOD;

	cout << cnt;
	return 0;
}
