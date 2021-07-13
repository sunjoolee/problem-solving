#include <iostream>
#include <algorithm>
using namespace std;

//2^28 = 2^30 = (10^3)^3 = 10^9
const int MAXN = 4000 ;
const int MAXSIZE = 4000 * 4000;

int n;
long long a[MAXN + 1];
long long b[MAXN + 1];
long long c[MAXN + 1];
long long d[MAXN + 1];
long long sumAB[MAXSIZE + 1];

void getSumAB() {
	int idx = 0;
	for(int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			sumAB[idx] = a[i] + b[j];
			++idx;
		}
	return;
}

long long getCnt() {
	long long cnt = 0;
	long long sumCD;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			sumCD = c[i] + d[j];

			int lb = lower_bound(sumAB, sumAB + (n * n), -sumCD) - sumAB;
			int ub = upper_bound(sumAB, sumAB + (n * n), -sumCD) - sumAB;

			if (sumAB[lb] + sumCD == 0)
				cnt += (ub - lb);
		}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i] >> b[i] >> c[i] >> d[i];
	
	getSumAB();
	sort(sumAB, sumAB + (n * n));
	cout << getCnt();
	return 0;
}