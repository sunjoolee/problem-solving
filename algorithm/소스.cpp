#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//도시의 개수, 두 도시를 연결하는 철도의 개수
int n, m;

//그래프의 인접 리스트 표현
vector<vector<int>> adj;

//dfsAll을 통해 방문한 정점
vector<int> visited;

//dfs를 통해 방문한 컴포넌트에 포함된 정점
vector<int> component;

//철도 여행 횟수
int cnt = 0;

void dfs(int here) {
	visited[here] = 1;

	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if (!visited[there])
			dfs(there);
	}
	component.push_back(here);
}

void dfsAll() {
	visited = vector<int>(n, 0);

	for (int i = 0; i < n; ++i) {
		if (!visited[i]) {
			component.clear();
			dfs(i);

			//철도가 연결되지 않은 도시인 경우 철도 여행 횟수에 포함되지 않는다
			if (component.size() == 1 && adj[i].size() == 0) continue;

			//방문한 컴포넌트의 모든 정점을 방문하기 위해 필요한 철도 여행의 수 계산
			int oddNode = 0;
			for (int i = 0; i < component.size(); ++i) {
				int node = component[i];
				if(adj[node].size() % 2) oddNode++;
			}

			if (oddNode == 0 || oddNode == 2) cnt += 1;
			else cnt += (oddNode / 2);
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;

	adj = vector<vector<int>>(n, vector<int>(0));
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;

		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}

	dfsAll();
	cout << cnt;
	return 0;
}