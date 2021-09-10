#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct OptimizedDisjointSet {
	vector<int> parent, rank;

	OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}
	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}
	void merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) return;

		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) ++rank[v];
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	cin >> n >> m;

	OptimizedDisjointSet ods(n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int input;
			cin >> input;

			if (input == 1) 
				ods.merge(i, j);
		}
	}

	bool flag = true;
	int start, dest;

	cin >> start;
	for(int i = 1; i<m; ++i){
		cin >> dest;
		if (ods.find(start - 1) != ods.find(dest - 1)) {
			flag = false;
			break;
		}
		start = dest;
	}

	if (flag) cout << "YES";
	else cout << "NO";
	return 0;
}