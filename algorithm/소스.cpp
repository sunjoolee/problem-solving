#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);

	int begin = 1;
	int matched = 0;
	while (begin + matched < m) {
		if (N[matched] == N[begin + matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

int getLongestPatialMatch(const string& s) {
	
	int ret = 0;

	//s[i..]에 대해 부분 일치 테이블 계산
	for (int i = 0; i < s.size(); ++i) {
		vector<int> pi = getPartialMatch(s.substr(i));

		for (int j = 0; j < pi.size(); ++j) {
			ret = max(ret, pi[j]);
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string s;
	cin >> s;
	cout << getLongestPatialMatch(s);

	return 0;
}
