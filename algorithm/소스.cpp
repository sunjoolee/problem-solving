#include <iostream>
using namespace std;

int n;
int cnt = 0;

//digit-1번째 자리의 수까지의 합이 digitsum일 때, digit번째 수를 고른다
void dp(int digit, int digitsum) {
	//N번째 수까지 모두 완성한 경우
	if (digit > n) {
		if (digitsum == 0) ++cnt;
		return;
	}

	//digit번째 자리의 수 0
	dp(digit + 1, digitsum);
	//digit번째 자리의 수 1
	dp(digit + 1, (digitsum + 1 )% 3);
	//digit번째 자리의 수 2
	dp(digit + 1, (digitsum + 2) % 3);

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;

	//첫번째 자리의 수 1
	dp(2, 1);
	//첫번째 자리의 수 2
	dp(2, 2);

	cout << cnt;
	return 0;
}