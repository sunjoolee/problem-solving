#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;


bool isPalindrome(string str) {
	if (str == "") return true;

	int len = str.length();
	if (len % 2 != 0) return false;

	for (int i = 0; i < len/ 2; ++i) {
		if (str[i] != str[len - i-1]) return false;
	}
	return true;
}

int maxCnt = -1;
map<string, int> cache;

void dp(string tmp, string A, int cnt) {
	if (A == "") {
		if (tmp == "") maxCnt = max(maxCnt,cnt);
		return;
	}

	if (cache.find(A) != cache.end()) {
		if (cache[A] > cnt) return;
	}
	else cache[A] = cnt;

	if (isPalindrome(tmp + A[0])) 
		dp("", A.substr(1), cnt + 1);

	dp(tmp + A[0], A.substr(1), cnt);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	string A = "";
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		A += to_string(a);
	}

	dp("", A, 0);

	if (maxCnt == 0) cout << -1;
	else cout << maxCnt;

	return 0;
}