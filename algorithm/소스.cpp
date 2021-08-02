#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int H;
	cin >> H;

	//dp[h]: 높이가 h일 때 필요한 차의 개수
	ull dp[61];
	
	dp[0] = 1;
	dp[1] = 1;
	
	//현재 높이가 h일 때
	//높이가 0 일 때 필요한 차의 개수의 합 + ... + 높이가 h-2 일 때 필요한 차의 개수의 합
	ull psum = 1;

	for (int h = 2; h <= H; ++h) {
		dp[h] = 1 + (2 * psum);
		psum += dp[h - 1];
	}

	cout << dp[H];

	return 0;
}