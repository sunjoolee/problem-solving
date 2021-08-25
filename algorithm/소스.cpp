#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;
const int MOD = 1000000009;

int n;
ll cache[33334];

//digit-1��° �ڸ��� �������� ���� digitsum�� ��, digit��° ���� ����
ll dp(int digit, int digitsum) {
	//N��° ������ ��� �ϼ��� ���
	if (digit > n) {
		if (digitsum == 0) return 1;
		else return 0;
	}

	ll& ret = cache[digit];
	if (ret != -1) return ret;

	ret = dp(digit + 1, digitsum);
	ret %= MOD;
	ret += dp(digit + 1, (digitsum + 1 )% 3);
	ret %= MOD;
	ret += dp(digit + 1, (digitsum + 2) % 3);
	ret %= MOD;

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	memset(cache, -1, sizeof(cache));

	cin >> n;

	ll res = dp(2, 1) + dp(2, 2);
	cout << res % MOD;
	return 0;
}