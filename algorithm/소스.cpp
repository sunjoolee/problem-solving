#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
string S, P;

vector<int> getPartialMatch() {

	vector<int> pi(m, 0);

	//begin = 0이면 자기 자신을 찾아버리므로 begin = 1부터 시작
	int begin = 1;
	int matched = 0;

	while (begin + matched < m) {
		if (S[begin + matched] >= '0' && S[begin + matched] <= '9') {
			++begin;
		}
		else if (S[begin + matched] == P[matched]) {
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

int found() {
	vector<int> pi = getPartialMatch();

	int begin = 0, matched = 0;
	while (begin <= n - m) {
		if (S[begin + matched] >= '0' && S[begin + matched] <= '9') {
			++begin;
		}
		else if (matched < m && S[begin + matched] == P[matched]) {
			++matched;
			if (matched == m) return 1;
		}
		else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 0;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> S >> P;
	n = S.size();
	m = P.size();

	cout << found();

	return 0;
}