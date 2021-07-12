#include <iostream>
using namespace std;

typedef unsigned long int ul;
const int MAXN = 100000 + 1;

int N;
ul S;
int num[MAXN];
ul psum[MAXN];

void getpsum() {
	psum[0] = num[0];
	for (int i = 1; i < N; ++i)
		psum[i] = psum[i - 1] + num[i];
	return;
}

int getlen() {
	if (psum[N-1] < S) return 0;

	for (int len = 1; len <= N; ++len) {
		//start = 0
		if (psum[len - 1] > S) return len;
		//start = 1 ~
		for (int start = 1; start + len - 1 < N; ++start)
			if (psum[start + len - 1] - psum[start-1] > S)
				return len;
	}

}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> S;
	for (int i = 0; i < N; ++i)
		cin >> num[i];

	getpsum();
	cout << getlen();
	return 0;
}