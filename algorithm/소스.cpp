#include <iostream>
using namespace std;

typedef unsigned long int ul;
const int MAXN = 10000 + 1;

int N;
ul M;
int A[MAXN];
ul psum[MAXN];

void getpsum() {
	psum[0] = 0;
	for (int i = 1; i <= N; ++i)
		psum[i] = psum[i - 1] + A[i];
	return;
}

ul getCnt() {
	ul ret = 0;
	for (int i = 1; i <= N; ++i)
		for (int j = i; j <= N; ++j)
			if (psum[j] - psum[i - 1] == M)
				++ret;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; ++i)
		cin >> A[i];

	getpsum();
	cout << getCnt();
	return 0;
}