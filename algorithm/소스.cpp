#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 30;
const int MAXW = 40000;

//Ãß
int n;
int marble;
int w[MAXN + 1];
int cache[MAXN][MAXW + 1];

int possible(int index, int sum) {
	if (sum == marble) return 1;
	if (index == n) return 0;

	int& ret = cache[index][sum];
	if (ret != -1) return ret;

	ret = possible(index + 1, sum);
	ret = max(ret, possible(index + 1, sum + w[index]));
	ret = max(ret, possible(index + 1, sum - w[index]));
	return ret;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> w[i];
	}

	int k;
	cin >> k;
	while (k--) {
		memset(cache, -1, sizeof(cache));
		cin >> marble;
		
		if (possible(0, 0)) cout << "Y" << "\n";
		else cout << "N" << "\n";
	}
	return 0;
}