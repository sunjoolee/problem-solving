#include <iostream>
using namespace std;

typedef unsigned long int ul;
const int MAXN = 10000 + 1;

int N;
ul M;
int A[MAXN] = { 0 };


ul getCnt() {
	ul ret = 0;
	int start = 0;
	int end = 0;
	ul psum = 0;

	while (end <= N) {
		if (psum >= M)
			psum -= A[start++];
		else if (psum < M)
			psum += A[end++];

		if (psum == M)
			ret++;
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; ++i)
		cin >> A[i];

	cout << getCnt();
	return 0;
}