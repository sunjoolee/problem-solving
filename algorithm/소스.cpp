
#include <iostream>
#include <cstring>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

const int MAXN = 100000;
int cache[MAXN + 1];
int sum[MAXN + 1];
int isPrime[MAXN + 1];
vector<int> prime;

//�����佺�׳׽��� ü
void setIsPrime() {
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[0] = isPrime[1] = 0;

	for (int i = 2; i <= sqrt(MAXN); i++) {
		if (isPrime[i] == 0) continue;

		for (int j = i * i; j <= MAXN; j += i)
			isPrime[j] = 0;
	}
	return;
}

void getPrime() {
	for (int i = 2; i <= MAXN; ++i)
		if (isPrime[i]) 
			prime.push_back(i);
	return;
}

//���� ���̿� ���� ���ڰ� N�� �� 
//���� ���ʰ� �̱� �� ������ 1, ���� 0 ��ȯ
int canWin(int N) {
	if (N == 0 || N == 1) return 0;
	if (isPrime[N]) return 1;

	int& ret = cache[N];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < prime.size(); ++i) {
		if (prime[i] > N) break;
		//���� ���ʿ��� ���� ��쿡 ���� ���ʿ��� �̱� �� �ִ�
		if (!canWin(N - prime[i])) {
			ret = 1;
			break;
		}
	}
	return ret;
}

void getSum() {
	memset(sum, 0, sizeof(sum));

	for (int N = 2; N <= MAXN; ++N)
		sum[N] = sum[N - 1] + !canWin(N);

	return;
}

void getX(int A, int k) {
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
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	setIsPrime();
	getPrime();
	getSum();

	int T;
	cin >> T;
	while (T--) {
		int A, k;
		cin >> A >> k;
		getX(A, k);
	}

	return 0;
}