#include <iostream>
#include <string>
#include <queue>
#include <set>
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

int bfs(string A) {

	priority_queue<pair<int, pair<string, string>>> q;
	q.push({ 0,{ "", A } });

	set<pair<string, string>> visited;

	while (!q.empty()) {
		int cnt = q.top().first;
		string tmp = q.top().second.first;
		string a = q.top().second.second;
		q.pop();

		//visited
		if (visited.find({ tmp, a }) != visited.end()) continue;
		visited.insert({ tmp, a });

		//base case
		if (a == "") {
			if (tmp == "") return cnt;
			else continue;
		}

		if (isPalindrome(tmp + a[0])) {
			if (visited.find({ "", a.substr(1) }) == visited.end()) {
				q.push({ cnt + 1,{"", a.substr(1)} });
			}
		}

		if (visited.find({ tmp + a[0], a.substr(1) }) == visited.end()) {
			q.push({ cnt,{tmp + a[0], a.substr(1)} });
		}
	}
	return -1;
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

	cout <<  bfs(A);

	return 0;
}