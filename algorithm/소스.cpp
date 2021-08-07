#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> edge[100001];

int visited[100001] = { 0 };
int parent[100001] = { 0 };

void dfs(int curnode, int parentnode) {

	parent[curnode] = parentnode;
	visited[curnode] = 1;

	for (int i = 0; i < edge[curnode].size(); ++i) {
		int nextnode = edge[curnode][i];
		if (visited[nextnode] == 0)
			dfs(nextnode, curnode);
	}
	return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		
		edge[a].push_back(b);
		edge[b].push_back(a);
	}

	dfs(1, 0);

	for(int i = 2; i<=n; ++i)
		cout << parent[i]<<"\n";

	return 0;
}