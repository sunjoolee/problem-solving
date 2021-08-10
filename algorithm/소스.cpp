#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

ull n, k;

//���� ����: ���� x�տ� k�� Ȥ�� k�� �̻��� ���ڰ� �����ϴ°�?

bool decision(int x) {
	ull cnt = 0;
	for (ull i = 1; i <= n; ++i)
		cnt += min(x / i, n);

	return cnt >= k;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> k;

	ull hi = 100000 * 100000;
	ull lo = 1;
	for (int it = 0; it < 100; ++it) {
		double mid = (hi + lo) / 2;

		if (decision(mid)) hi = mid;
		else lo = mid;
	}

	cout << hi;

	return 0;
}