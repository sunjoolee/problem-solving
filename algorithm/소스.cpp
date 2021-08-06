#include <iostream>
#include <vector>
using namespace std;

//트리의 리프 노드들의 깊이의 합
int sum = 0;

vector<vector<int>> edge (500001);
int visited[500001] = { 0 };

void dfs(int node, int depth) {

	//리프노드 만나면 종료
	//간선의 수 1개인 노드 = 리프 노드
	if (node != 1 && edge[node].size() == 1) {
		sum += depth;
		return;
	}
	
	visited[node] = 1;

	for(int i = 0; i<edge[node].size(); ++i){
		if (!visited[edge[node][i]])
			dfs(edge[node][i], depth + 1);
	}


	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;

		edge[a].push_back(b);
		edge[b].push_back(a);
	}

	//루트 노드부터 DFS
	dfs(1, 0);
	
	//sum 홀수인 경우 성원이 승리
	if (sum % 2) cout << "Yes";
	else cout << "No";

	return 0;
}