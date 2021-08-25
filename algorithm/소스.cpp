#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int N, Q;

struct FenwickTree {
	vector<ll> tree;

	FenwickTree(int size) : tree(size + 1) {}

	ll sum(int pos) {
		ll ret = 0LL;
		while (pos > 0) {
			ret += tree[pos];

			//0이 아닌 마지막 비트만큼 빼면서 구간들의 값 변경
			pos -= (pos & -pos);
		}
		return ret;
	}

	void add(int pos, ll val) {
		while (pos < tree.size()) {
			tree[pos] += val;
			//0이 아닌 마지막 비트만큼 더하면서 구간들의 값 변경
			pos += (pos & -pos);
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> Q;

	FenwickTree fenwickTree(N);

	for (int i = 1; i <= N; ++i) {
		ll input;
		cin >> input;
		fenwickTree.add(i, input);
	}

	while(Q--) {
		int x, y; 
		cin >> x >> y;
		
		if(x > y) cout << fenwickTree.sum(x) - fenwickTree.sum(y - 1) << "\n";
		else cout << fenwickTree.sum(y) - fenwickTree.sum(x - 1) << "\n";

		int a; ll b;
		cin >> a >> b;

		b = b - (fenwickTree.sum(a) - fenwickTree.sum(a - 1));
		fenwickTree.add(a, b);
	}

	return 0;
}