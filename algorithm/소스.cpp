#include <iostream>
#include <map>
using namespace std;

const int MAXN = 40;

int n, s;
long long cnt = 0;
int num[MAXN + 1]; 
map<int, int> mp;

void dfsLeft(int index, int sum) {
	if (index == n/2) {
		++mp[sum];
		return;
	}
	dfsLeft(index + 1, sum);
	dfsLeft(index + 1, sum + num[index]);
	return;
}

void dfsRight(int index, int sum) {
	if (index >= n) {
		cnt += mp[s-sum];
		return;
	}
	dfsRight(index + 1, sum);
	dfsRight(index + 1, sum + num[index]);
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> s;
	for (int i = 0; i < n; ++i)
		cin >> num[i];

	dfsLeft(0, 0);
	dfsRight(n/2, 0);

	if (s == 0) cnt--;
	cout << cnt;
	return 0;
}