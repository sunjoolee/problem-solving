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

vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size();
	int m = N.size();

	vector<int> ret;
	vector<int> pi = getPartialMatch(N);

	int begin = 0, matched = 0;
	while (begin <= n - m) {
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m) ret.push_back(begin);
		}
		else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string T;
	getline(cin, T);

	string P;
	getline(cin, P);

	vector<int> kmp = kmpSearch(T, P);
	
	cout << kmp.size()<<"\n";
	for (auto it = kmp.begin(); it != kmp.end(); ++it)
		cout << *it + 1 << " ";

	return 0;
}
