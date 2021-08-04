#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

bool compare(pair<pair<int, int>, string> a, pair<pair<int, int>, string> b) {
	//나이순 정렬
	if (a.first.first < b.first.first) return true;
	//나이 같다면 가입한 순서대로 정렬
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

	//<<나이, 가입 순서>, 이름>
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