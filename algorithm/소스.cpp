#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 300;
const int MAXM = 20;

int n, m;

//[company][money]
int profit[MAXM + 1][MAXN + 1];
int cache[MAXM + 1][MAXN + 1];
int bestChoice[MAXM + 1][MAXN + 1] = { 0 };

int getMaxProfit(int company, int money) {
	if (company > m || money == 0) return 0;

	int& ret = cache[company][money];
	if (ret != -1) return ret;

	int choice = 0;
	ret = getMaxProfit(company + 1, money);

	for (int i = 1; i <= money; ++i) {
		int cand = profit[company][i] + getMaxProfit(company + 1, money - i);
		if (ret < cand) {
			ret = cand;
			choice = i;
		}
	}

	bestChoice[company][money] = choice;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cache, -1, sizeof(cache));

	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		int money;
		cin >> money;
		for (int j = 1; j <= m; ++j)
			cin >> profit[j][i];
	}

	cout << getMaxProfit(1, n) << "\n";

	int sumOfChoice = 0;
	for (int i = 1; i <= m; ++i) {
		int choice = bestChoice[i][n - sumOfChoice];
		cout << choice << " ";
		sumOfChoice += choice;
	}
	return 0;
}