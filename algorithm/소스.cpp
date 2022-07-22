#include <iostream>
#include<algorithm>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	int cnt = 0;
	for (int x = 1; x <= n; ++x) {
		vector<int> digit;
		int tmp = x;
		while (tmp != 0) {
			digit.push_back(tmp % 10);
			tmp /= 10;
		}
		//등차수열 이루는지 검사
		if (digit.size() < 3) cnt++;
		else {
			bool flag = true;
			int sub = digit[0] - digit[1];
			for (int i = 0; i < digit.size() -1; ++i) {
				if ((digit[i] - digit[i + 1]) != sub) {
					flag = false;
					break;
				}
			}
			if (flag) cnt++;
		}
	}

	cout << cnt;
	return 0;
}