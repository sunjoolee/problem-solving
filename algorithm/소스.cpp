#include <iostream>
using namespace std;

int n;
int cnt = 0;

//digit-1��° �ڸ��� �������� ���� digitsum�� ��, digit��° ���� ����
void dp(int digit, int digitsum) {
	//N��° ������ ��� �ϼ��� ���
	if (digit > n) {
		if (digitsum == 0) ++cnt;
		return;
	}

	//digit��° �ڸ��� �� 0
	dp(digit + 1, digitsum);
	//digit��° �ڸ��� �� 1
	dp(digit + 1, (digitsum + 1 )% 3);
	//digit��° �ڸ��� �� 2
	dp(digit + 1, (digitsum + 2) % 3);

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;

	//ù��° �ڸ��� �� 1
	dp(2, 1);
	//ù��° �ڸ��� �� 2
	dp(2, 2);

	cout << cnt;
	return 0;
}