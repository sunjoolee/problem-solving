#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

vector<int> edge[1001];
int visited[1001];

void dfs(int curnode) {
	cout << curnode << " ";
	visited[curnode] = 1;

	for (int i = 0; i < edge[curnode].size(); ++i) {
		int nextnode = edge[curnode][i];

		if (visited[nextnode] == 0)
			dfs(nextnode);
	}
	return;
}

void bfs(int startnode) {
	queue<int> q;
	q.push(startnode);

	while (!q.empty()) {
		int curnode = q.front();
		q.pop();

		if(visited[curnode] == 1)
			continue;

		cout << curnode << " ";
		visited[curnode] = 1;

		for (int i = 0; i < edge[curnode].size(); ++i) {
			int nextnode = edge[curnode][i];

			if (visited[nextnode] == 0)
				q.push(nextnode);
		}

	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, v;
	cin >> n >> m >> v;

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}

	for (int i = 1; i <= n; ++i)
		sort(edge[i].begin(), edge[i].end());

	memset(visited, 0, sizeof(visited));
	dfs(v);
	cout << "\n";
	memset(visited, 0, sizeof(visited));
	bfs(v);

	return 0;
}