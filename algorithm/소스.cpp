#include<algorithm>
#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;

int n;
ll m;
vector<ll> trees;

//높이를 h로 지정했을 때 m미터 이상의 나무를 가져갈 수 있는가
bool check(ll h) {
	ll takeTree = 0;
	for (int i = 0; i < n; ++i) {
		if (trees[i] > h) takeTree += (trees[i] - h);
	}
	return takeTree >= m;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		ll input;
		cin >> input;
		trees.push_back(input);
	}

	ll high = 1000000000;
	ll low = 0LL;
	while (low < high) {
		ll mid = (high + low + 1) / 2;
		if (check(mid)) low = mid;
		else high = mid - 1;
	}

	cout << high;
	return 0;
}