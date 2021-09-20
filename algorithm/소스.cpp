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

	//��� ������ �湮�� ������ dfs�� ȣ���ؾ��ϴ� Ƚ��
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

	//��� ���� �ϳ��� ������Ʈ�� ���ԵǾ� �ִ°�
	int component = dfsAll();
	if (component > 1) {
		cout << "NO";
		return 0;
	}

	//���Ϸ� ��Ŷ/Ʈ���� �����ϴ��� �˻�
	//�׷����� ��� ������ ¦���� -> ���Ϸ� ��Ŷ ����
	//�׷����� �� ���� Ȧ���� & ������ ��� ���� ¦���� -> ���Ϸ� Ʈ���� ����
	int cnt = 0;
	for (int k = 0; k < V; ++k) {
		if (adj[k].size() % 2) ++cnt;
	}

	if (cnt == 0 || cnt == 2) cout << "YES";
	else cout << "NO";
	
	return 0;
}