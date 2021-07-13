#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long int ul;
const int MAXN = 100000 + 1;

int N;
ul S;
int num[MAXN];

int getlen() {
	//base case
	if (S == 0) return 1;

	int minlen = MAXN;
	int start = 0;
	int end = 0;
	ul psum = 0;

	while (end <= N) {
		if (psum >= S) {
			minlen = min(minlen, (end - 1) - start + 1);
			psum -= num[start++];
		}
		else if (psum < S)
			psum += num[end++];

	}

	if (minlen == MAXN) return 0;
	else return minlen;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> S;
	for (int i = 0; i < N; ++i)
		cin >> num[i];

	cout << getlen();
	return 0;
}