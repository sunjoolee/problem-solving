#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//최적화된 상호 배타적 집합의 구현
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

	//0 ~ n까지 n+1 크기의 unionFind
	OptimizedDisjointSet unionFind(n+1);

	while (m--) {
		int input, a, b;
		cin >> input >> a >> b;

		//합집합 연산
		if (input == 0) {
			unionFind.merge(a, b);
		}
		//같은 집합에 포함되어있는지 확인 연산
		else if (input == 1) {
			if (unionFind.find(a) == unionFind.find(b)) 
				cout << "YES\n";
			else 
				cout << "NO\n";
		}
	}

	return 0;
}