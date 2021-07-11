#include <iostream>
#include <cstring>
#include <math.h>
#include <algorithm>
using namespace std;

const int MAXN = 100000;
int cache[MAXN][2];
int isPrime[MAXN];

void setIsPrime(){
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[0] = isPrime[1] = 0;
	
	for (int i = 2; i <= sqrt(MAXN); i++){
		if (isPrime[i] == 0) continue;

		for (int j = i * i; j <= MAXN; j += i)
			isPrime[j] = 0;
	}
	return;
}

//p가 이길 수 있으면 1, 지면 0 반환
int canWin(int N, int p) {
	if (N == 0 || N == 1) return 0;

	int& ret = cache[N][p];
	if (ret != -1) return ret;

	ret = 0; 
	for (int i = 2; i <= N; ++i) {
		if (isPrime[i])
			if (!canWin(N - i, 0 + 1 - p)) {
				ret = 1;
				break;
			}
	}
		
	return ret;
}

void getX(int A, int k) {

	int bestX = 0;
	int bestwin = 0;

	for (int X = A + 1 - k; X >= 2; --X) {
		
		int win = 0;
		for (int N = X; N <= X + k - 1; ++N) 
			if (!canWin(N, 0))
				++win;
		
		if (bestwin <= win ) {
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
	
	for (int i = 0; i < MAXN; ++i)
		memset(cache[i], -1, sizeof(cache[i]));

	setIsPrime();

	int T;
	cin >> T;
	while (T--) {

		int A, k;
		cin >> A >> k;
		getX(A, k);
	}

	return 0;
}