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

	//dp[h]: ���̰� h�� �� �ʿ��� ���� ����
	ull dp[61];
	
	dp[0] = 1;
	dp[1] = 1;
	
	//���� ���̰� h�� ��
	//���̰� 0 �� �� �ʿ��� ���� ������ �� + ... + ���̰� h-2 �� �� �ʿ��� ���� ������ ��
	ull psum = 1;

	for (int h = 2; h <= H; ++h) {
		dp[h] = 1 + (2 * psum);
		psum += dp[h - 1];
	}

	cout << dp[H];

	return 0;
}