#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MIN = -1001;

int N, S, M;
int V[100];
int cache[1000][100];

int getMaxVolume(int nowVolume, int i) {
	if (nowVolume > M || nowVolume < 0) return MIN;
	if (i == N) return nowVolume;

	int& ret = cache[nowVolume][i];
	if (ret != -1) return ret;

	return ret = max(getMaxVolume(nowVolume + V[i], i+1), getMaxVolume(nowVolume - V[i], i + 1));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for(int i = 0; i<1000; ++i)
		memset(cache[i], -1, sizeof(cache[i]));
	
	cin >> N >> S >> M;
	for (int i = 0; i < N; ++i)
		cin >> V[i];

	int maxV = getMaxVolume(S, 0);
	if (maxV == MIN) cout << -1;
	else cout << maxV;

	return 0;
}