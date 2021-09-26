#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> seen, order;

//깊이 우선 탐색을 진행하며 dfs종료 순서 기록
void dfs(int here) {
	seen[here] = 1;
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];

		if (!seen[there])
			dfs(there);
	}
	order.push_back(here);
}

void topologicalSort() {
	//dfsAll
	for (int i = 0; i < n; ++i) {
		if (!seen[i]) dfs(i);
	}
	
	reverse(order.begin(), order.end());

	for (int i = 0; i < order.size(); ++i)
		cout << order[i] +1<< " ";
	
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;

	adj = vector<vector<int>>(n, vector<int>(0));
	seen = vector<int>(n, 0);
	order.clear();

	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;

		adj[u - 1].push_back(v - 1);
	}

	topologicalSort();
	return 0;
}