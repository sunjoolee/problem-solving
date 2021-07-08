#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 101;

int N;
long long cache[MAX];

long long getScreen(int time) {

	long long &res = cache[time];
	if (res != -1) return res;

	//1초전 상태에 A 하나 추가
	res = 1 + getScreen(time - 1);

	if (time >= 3) {
		//(time- 2 - i)초 상태에 CtrlA + CtrlC + Σ(CtrlV)
		for (int i = 1; time - 2 - i >= 0; ++i) {
			res = max(res, getScreen(time - 2 - i) * (i + 1));
		}
	}
	return res;
}



int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> N;

	cache[0] = 0;
	cout << getScreen(N);
	return 0;
}