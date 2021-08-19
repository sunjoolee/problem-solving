#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

const int r = 31;
const ull M = 1234567891;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int L;
	string str;
	cin >> L >> str;

	ull H = 0;
	ull R = 1;
	for (int i = 0; i < L; ++i) {
		ull h = ((str[i] - 'a' + 1) * R) % M;

		H = (H + h) % M;

		R = (R * r) % M;
	}

	cout << H;
	return 0;
}