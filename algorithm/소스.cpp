#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

typedef long long ll;

int k;
vector<char> sign;
vector<int> arr;
bool num[10] = { 0 };

string maxArr = "0";
string minArr = "9876543210";

//k+1자리 배열이 k개의 부등호 만족하는지 검사
bool check() {
	for (int i = 0; i < k; ++i) {
		if ((sign[i] == '<')&&(arr[i] > arr[i + 1]))
			return false;
		if((sign[i] == '>') && (arr[i] < arr[i + 1]))
			return false;
	}
	return true;
}

void solve (int digit) {
	//k+1 자리 배열 생성 완료
	if (digit == k + 1) {
		if (check()) {
			string curArr = "";
			for (int i = 0; i < k + 1; ++i) {
				curArr += to_string(arr[i]);
			}

			maxArr = max(maxArr, curArr);
			minArr = min(minArr, curArr);
		}
		return;
	}

	for (int i = 0; i <= 9; ++i) {
		if (num[i]) continue;
		num[i] = true;
		arr.push_back(i);
		solve(digit + 1);
		arr.pop_back();
		num[i] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> k;

	for (int i = 0; i < k; ++i) {
		char input;
		cin >> input;
		sign.push_back(input);
	}

	solve(0);

	cout << maxArr << "\n";
	cout << minArr << "\n";
	return 0;
}