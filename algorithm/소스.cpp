#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

int N; 
int num[100];
ull cache[100][1000];

ull getCnt(int i, int val) {
	if (val < 0 || val > 20) 
		return 0;
	if (i == N - 1) {
		if (val == num[N - 1]) return 1;
		else return 0;
	}

	ull& ret = cache[i][val];
	if (ret != -1) return ret;

	return ret = getCnt(i + 1, val + num[i]) + getCnt(i + 1, val - num[i]);
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 100; ++i)
		memset(cache[i], -1, sizeof(cache[i]));

	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> num[i];

	cout << getCnt(0, 0);

	return 0;
}