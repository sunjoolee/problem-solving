#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

bool compare(pair<pair<int, int>, string> a, pair<pair<int, int>, string> b) {
	//���̼� ����
	if (a.first.first < b.first.first) return true;
	//���� ���ٸ� ������ ������� ����
	else if (a.first.first == b.first.first)
		return (a.first.second < b.first.second);
	else return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	//<<����, ���� ����>, �̸�>
	vector<pair<pair<int, int>, string>> v;
	for (int i = 0; i < n; ++i) {
		int age;
		string name;
		cin >> age >> name;
		v.push_back(make_pair(make_pair(age, i), name));
	}

	sort(v.begin(), v.end(), compare);
	
	for (int i = 0; i < n; ++i) {
		cout << v[i].first.first << " "<< v[i].second<<"\n";
	}
	return 0;
}