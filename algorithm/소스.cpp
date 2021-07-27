#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//각 접미사들의 첫 t 글자를 기준으로 한 그룹 번호가 주어질 때
//주어진 두 접미사를 첫 2t 글자를 기준으로 비교한다
//group[]은 길이가 0인 접미사도 포함한다
struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}

	bool operator() (int a, int b) {
		if (group[a] != group[b]) return group[a] < group[b];
		return group[a + t] < group[b + t];
	}
};

//접미사 배열 계산
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

//중복되는 부분 문자열의 길이 계산
int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j]) {
		++i; ++j; ++k;
	}
	return k;
}

//중복되는 부분 문자열의 길이 줄 가장 긴 길이 반환
int longestCommonSubstring(const string& s) {
	vector<int> a = getSuffixArray(s);

	int ret = 0;
	for (int i = 0; i < a.size(); ++i) {
		int cp = 0;
		if (i > 0) cp = commonPrefix(s, a[i - 1], a[i]);
	
		ret = max(ret, cp);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string s;
	cin >> s;

	cout << longestCommonSubstring(s);

	return 0;
}