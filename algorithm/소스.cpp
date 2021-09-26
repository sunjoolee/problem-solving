#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;

//inDegree[i]: ����i�� ���� ������ ��
vector<int> inDegree;
//child[i]: ���i�� ���� ���� �ϴ� ������ ����
vector<vector<int>> child;

//���� ���� �Լ�
void topologySort() {

	vector<int> result(n, 0);
	queue<int> q;

	//���� ���� 0�� ���� ť�� ����
	for (int i = 0; i < n; ++i)
		if (inDegree[i] == 0) q.push(i);
	
	//������ ������ ����Ǳ���� n���� ������ �湮�Ѵ�
	for (int i = 0; i < n; ++i) {
		//n���� ������ �湮�ϱ� ���� ť�� �������� 
		//����Ŭ�� �߻��� ���̴�
		if (q.empty()) return;

		//���� ������ 0�� ���� ����
		int parent = q.front();
		result[i] = parent;

		//���õ� ������ ���⿡ �μӵ� ��� ������ ����
		q.pop();
		for (int i = 0; i < child[parent].size(); ++i) {
			int childnode = child[parent][i];
			//���Ӱ� ���������� 0�� �� ������ ť�� ����
			if (--inDegree[childnode] == 0)
				q.push(childnode);
		}
	}

	//���� ���� ��� ���
	for (int i = 0; i < n; ++i)
		cout << result[i] + 1 << " ";

	return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;

	inDegree = vector<int>(n, 0);
	child = vector<vector<int>> (n, vector<int>(0));

	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;

		child[u-1].push_back(v - 1);
		inDegree[v - 1]++;
	}

	topologySort();
	return 0;
}