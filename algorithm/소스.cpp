#include <iostream>
#include <vector>
using namespace std;

//Ʈ���� ���� ������ ������ ��
int sum = 0;

vector<vector<int>> edge (500001);
int visited[500001] = { 0 };

void dfs(int node, int depth) {

	//������� ������ ����
	//������ �� 1���� ��� = ���� ���
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

	//��Ʈ ������ DFS
	dfs(1, 0);
	
	//sum Ȧ���� ��� ������ �¸�
	if (sum % 2) cout << "Yes";
	else cout << "No";

	return 0;
}