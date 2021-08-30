#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;


struct OptimizedDisjointSet {
	vector<int> parent, rank, size;

	OptimizedDisjointSet(int n) : parent(n), rank(n, 1), size(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}

	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	//u가 포함된 상호 배타적 집합 + v가 포함된 상호 배타적 집합
	//의 결과인 상호 배타적 집합의 크기 반환
	int merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) return size[u];

		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) ++rank[v];

		size[v] += size[u];
		return size[v];
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		//친구 관계의 수
		int f;
		cin >> f;

		map <string, int> name2node;
		OptimizedDisjointSet ods(2 * f);

		int nodeNo = 0;

		for (int i = 0; i < f; ++i) {
			string name1, name2;
			cin >> name1 >> name2;

			auto it = name2node.find(name1);
			if (it == name2node.end()) 
				name2node[name1] = nodeNo++;

			it = name2node.find(name2);
			if (it == name2node.end()) 
				name2node[name2] = nodeNo++;

			cout << ods.merge(name2node[name1], name2node[name2]) << "\n";
		}
	}
	return 0;
}