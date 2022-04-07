#include <string>
#include <vector>
#include <memory.h>
#include <algorithm>

using namespace std;

typedef long long int ll;

const int INF = 987654321;

int N;
vector<int> weakG;
vector<int> distG;

//cache[2^15 + 1][2^8 + 1]
//cache[방문된 weak 비트마스크] = 사용된 친구의 수
int cache[32769];

//w 지점에서 출발하여 시계방향으로 이동했을 때
//방문할 수 있는 취약 지점들의 비트마스크 반환
ll cw(int w, int fIdx) {
	ll res = 0LL;
	int pos = w;
	for (int d = 0; d < distG[fIdx]; ++d) {
		pos = w + d;
		if (pos > N) pos = N - pos;

		for (int i = 0; i < weakG.size(); ++i) {
			if(weakG[i] == pos) res |= (1 << i);
		}
	}
	return res;
}

//w 지점에서 출발하여 반시계방향으로 이동했을 때
//방문할 수 있는 취약 지점들의 비트마스크 반환
ll ccw(int w, int fIdx) {
	ll res = 0LL;
	int pos = w;
	for (int d = 0; d < distG[fIdx]; ++d) {
		pos = w - d;
		if (pos == 0) pos = N;

		for (int i = 0; i < weakG.size(); ++i) {
			if (weakG[i] == pos) res |= (1 << i);
		}
	}
	return res;
}

int bitCnt(ll x) {
	if (x == 0) return 0;
	return (x % 2) + bitCnt(x / 2);
}

void solve(ll weaks, ll friends) {
	cache[weaks] = min(cache[weaks], bitCnt(friends));

	for (int wIdx = 0; wIdx < weakG.size(); ++wIdx) {
		if (weaks & (1 << wIdx)) continue;

		int w = weakG[wIdx];
		for (int fIdx = 0; fIdx < distG.size(); ++fIdx) {
			if (friends & (1 << fIdx)) continue;

			if(cw(w, fIdx) != 0LL)
				solve(weaks | cw(w, fIdx), friends | (1 << fIdx));
			if(ccw(w, fIdx) != 0LL)
				solve(weaks | ccw(w, fIdx), friends | (1 << fIdx));
		}
	}
}

int solution(int n, vector<int> weak, vector<int> dist) {
	//cache 초기화
	for (int i = 0; i < (1 << weak.size()) - 1; ++i) {
		cache[i]= INF;
	}

	N = n;
	weakG = weak;
	distG = dist;

	solve(0LL, 0LL);

	if (cache[(1 << weak.size()) - 1] != INF) return cache[(1 << weak.size()) - 1];
	return -1;
}

int main() {
	solution(12, { 1, 5, 6, 10 }, {1, 2, 3, 4});
}