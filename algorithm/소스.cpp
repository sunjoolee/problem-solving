#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

struct nation {
	int num;
	int gold;
	int silver;
	int bronze;

	nation(int n, int g, int s, int b) : num(n), gold(g), silver(s), bronze(b){}
};

bool cmp(nation a, nation b) {
	if (a.gold > b.gold) return true;
	else if (a.gold == b.gold) {
		if (a.silver > b.silver) return true;
		else if (a.silver == b.silver) return a.bronze > b.bronze;
		else return false;
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int N, k;
	cin >> N >> k;

	vector<nation> vec;

	for (int i = 0; i < N; ++i) {
		int n, g, s, b;
		cin >> n >> g >> s >> b;
		vec.push_back(nation(n, g, s, b));
	}
	sort(vec.begin(), vec.end(), cmp);

	int rating = 1;
	if (vec[0].num != k) {
		for (int i = 1; i < N; ++i) {
			if ((vec[i - 1].gold != vec[i].gold)
				|| (vec[i - 1].silver != vec[i].silver)
				|| (vec[i - 1].bronze != vec[i].bronze)) {
				rating = i + 1;
			}

			if (vec[i].num == k) break;
		}
	}
	cout << rating;
	return 0;
}