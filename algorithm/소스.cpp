#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 500 + 1;

int N, K;
int a[MAXN];
int cache[MAXN][MAXN];

int getMaxLen(int index, int k) {
	if (index >= N || k > K) return 0;

	int& ret = cache[index][k];
	if (ret != -1) return ret;

	ret = 1;
	for (int next = index + 1; next < N; ++next) {
		if (a[index] <= a[next])
			ret = max(ret, 1 + getMaxLen(next, k));
		else if (a[index] > a[next])
			ret = max(ret, 1 + getMaxLen(next, k+1));
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> N >> K;
	for (int i = 0; i < N; ++i)
		cin >> a[i];
	
	cout << getMaxLen(0, 0);
	return 0;
}