#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//����ȭ�� ��ȣ ��Ÿ�� ������ ����
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

	//0 ~ n���� n+1 ũ���� unionFind
	OptimizedDisjointSet unionFind(n+1);

	while (m--) {
		int input, a, b;
		cin >> input >> a >> b;

		//������ ����
		if (input == 0) {
			unionFind.merge(a, b);
		}
		//���� ���տ� ���ԵǾ��ִ��� Ȯ�� ����
		else if (input == 1) {
			if (unionFind.find(a) == unionFind.find(b)) 
				cout << "YES\n";
			else 
				cout << "NO\n";
		}
	}

	return 0;
}