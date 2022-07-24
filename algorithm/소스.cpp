#include <algorithm>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;

	vector<int> vecS;
	vector<int> vecB;
	
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int inputS, inputB;
		cin >> inputS >> inputB;
		vecS.push_back(inputS);
		vecB.push_back(inputB);
	}

	int s; //¿ä¸®ÀÇ ½Å¸À(°ö)
	int b; //¿ä¸®ÀÇ ¾´¸À (ÇÕ)
	int ans = 1000000000;
	
	int fullSet = (1<<n) - 1; 
	for (int set = 1; set <= fullSet; set++) {
		s = -1;
		b = -1;
		for (int food = 0; food < n; ++food) {
			if (set & (1 << food)) {
				if (s == -1) s = vecS[food];
				else s *= vecS[food];

				if (b == -1) b = vecB[food];
				else b += vecB[food];
			}
		}
		ans = min(ans, abs(s - b));
	}

	cout << ans;
	return 0;
}