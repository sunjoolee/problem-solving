#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}

	bool operator() (int a, int b) {
		if (group[a] != group[b]) return group[a] < group[b];
		return group[a + t] < group[b + t];
	}
};

//s�� ���̻� �迭�� ����Ѵ�
vector<int> getSuffixArray(const string& s) {
	int n = s.size();

	int t = 1;
	vector<int> group(n + 1);
	group[n] = -1;

	for (int i = 0; i < n; ++i)
		group[i] = s[i];

	vector<int> perm(n);
	for (int i = 0; i < n; ++i)
		perm[i] = i;

	while (t < n) {
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);

		t *= 2;
		if (t >= n) break;

		vector<int> newGroup(n + 1);
		newGroup[n] = -1;

		for (int i = 1; i < n; ++i) {
			if (compareUsing2T(perm[i - 1], perm[i])) {
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			}
			else {
				newGroup[perm[i]] = newGroup[perm[i - 1]];
			}
		}
		group = newGroup;
	}
	return perm;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string s;
	cin >> s;

	vector<int> suffixArray = getSuffixArray(s);

	for (int i = 0; i < suffixArray.size(); ++i) {
		cout << s.substr(suffixArray[i]) << "\n";
	}


	return 0;
}