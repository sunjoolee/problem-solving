#include <iostream>
#include <cstring>
#include <math.h>
#include <algorithm>
using namespace std;

const int MAXN = 123456 * 2;

//�Ҽ��� 0, �Ҽ��� �ƴϸ� 1 ����
int notPrime[MAXN + 1] = { 0 };

//�����佺�׳׽��� ü
void eratos() {
	notPrime[0] = notPrime[1] = 1;

	for (int i = 2; i <= sqrt(MAXN); i++) {
		if (notPrime[i] == 1) continue;

		for (int j = i * i; j <= MAXN; j += i)
			notPrime[j] = 1;
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	eratos();

	int psum[MAXN + 1] = { 0 };
	for (int i = 1; i <= MAXN; ++i)
		psum[i] = psum[i - 1] + !notPrime[i];

	int n;
	while (true) {
		cin >> n;
		if (n == 0) break;

		cout << psum[2 * n] - psum[n] << "\n";
	}
	return 0;
}