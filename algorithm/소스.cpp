#include <iostream>
#include <cstring>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

const int MAXN = 100000;
int canWin[MAXN + 1] = { 0 };
int sum[MAXN + 1] = { 0 };
int isPrime[MAXN + 1];
vector<int> prime;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//�����佺�׳׽��� ü
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[0] = isPrime[1] = 0;
	for (int i = 2; i <= sqrt(MAXN); i++) {
		if (isPrime[i] == 0) continue;

		for (int j = i * i; j <= MAXN; j += i)
			isPrime[j] = 0;
	}

	//�Ҽ� ���Ϳ� ����
	for (int i = 2; i <= MAXN; ++i)
		if (isPrime[i])
			prime.push_back(i);

	//���̿� ���� ���� N�� �� �̱� �� �ִ��� ����
	int psize = prime.size();
	for (int i = 0; i <= MAXN; i++) {
		if (canWin[i])
			continue;
		for (int j = 0; j < psize; j++)
		{
			if (i + prime[j] > MAXN)
				break;
			canWin[i + prime[j]] = 1;
		}
	}

	//�¸��ϴ� ����� �� �κ��� ���
	for (int N = 2; N <= MAXN; ++N)
		sum[N] = sum[N - 1] + !canWin[N];


	int T;
	cin >> T;
	while (T--) {
		int A, k;
		cin >> A >> k;

		int bestX = 0;
		int bestwin = 0;

		for (int X = A + 1 - k; X >= 2; --X) {
			int win = sum[X + k - 1] - sum[X - 1];
			if (bestwin <= win) {
				bestwin = win;
				bestX = X;
			}
		}
		cout << bestwin << " " << bestX << "\n";
	}

	return 0;
}