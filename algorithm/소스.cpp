#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long int ul;
const ul MAXN = 4000000;

int N;
vector <int> prime;
int isPrime[MAXN + 1];

//에라토스테네스의 체
void getPrime(int N) {
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[0] = isPrime[1] = 0;

	for (int i = 2; i <= sqrt(N); i++) {
		if (isPrime[i] == 0) continue;

		prime.push_back(i);
		for (int j = i * i; j <= N; j += i)
			isPrime[j] = 0;
	}

	for (int i = sqrt(N)+1; i <= N; i++)
		if (isPrime[i])
			prime.push_back(i);
	return;
}

int getCnt() {
	int ret = 0;
	int start = 0;
	int end = 0;
	ul psum = 0;

	prime.push_back(0);
	while (end < prime.size()) {
		if (psum >= N)
			psum -= prime[start++];

		else if (psum < N)
			psum += prime[end++];

		if (psum == N)
			ret++;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	getPrime(N);
	cout << getCnt();

	return 0;
}