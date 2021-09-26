#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//������ ����, �� ���ø� �����ϴ� ö���� ����
int n, m;

//�׷����� ���� ����Ʈ ǥ��
vector<vector<int>> adj;

//dfsAll�� ���� �湮�� ����
vector<int> visited;

//dfs�� ���� �湮�� ������Ʈ�� ���Ե� ����
vector<int> component;

//ö�� ���� Ƚ��
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

			//ö���� ������� ���� ������ ��� ö�� ���� Ƚ���� ���Ե��� �ʴ´�
			if (component.size() == 1 && adj[i].size() == 0) continue;

			//�湮�� ������Ʈ�� ��� ������ �湮�ϱ� ���� �ʿ��� ö�� ������ �� ���
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