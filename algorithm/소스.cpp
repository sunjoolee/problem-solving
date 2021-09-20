#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int V, E;

vector<vector<int>> adj(3001);
vector<bool> visited;

void dfs(int here) {
	visited[here] = true;

	for (int i = 0; i < adj[here].size(); ++i) { 
		int there = adj[here][i];
		if (!visited[there]) 
			dfs(there);
	}
}

int dfsAll() {
	visited = vector<bool>(V, false);

	//모든 정점이 방문될 때까지 dfs를 호출해야하는 횟수
	int cnt = 0;
	for (int i = 0; i < V; ++i) {
		if (!visited[i]) {
			dfs(i);
			++cnt;
		}
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> V >> E;

	for (int i = 0; i < E; ++i) {
		int a, b;
		cin >> a >> b;

		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}

	//모든 간선 하나의 컴포넌트에 포함되어 있는가
	int component = dfsAll();
	if (component > 1) {
		cout << "NO";
		return 0;
	}

	//오일러 서킷/트레일 존재하는지 검사
	//그래프의 모든 정점이 짝수점 -> 오일러 서킷 존재
	//그래프의 두 정점 홀수점 & 나머지 모든 정점 짝수점 -> 오일러 트레일 존재
	int cnt = 0;
	for (int k = 0; k < V; ++k) {
		if (adj[k].size() % 2) ++cnt;
	}

	if (cnt == 0 || cnt == 2) cout << "YES";
	else cout << "NO";
	
	return 0;
}