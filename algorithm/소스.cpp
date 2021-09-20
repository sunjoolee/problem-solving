#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;

vector<vector<int>> adj(1001);
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
	visited = vector<bool>(N, false);

	//��� ������ �湮�� ������ dfs�� ȣ���ؾ��ϴ� Ƚ��
	int cnt = 0;
	for (int i = 0; i < N; ++i) {
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

	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;

		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}

	cout << dfsAll();
	return 0;
}