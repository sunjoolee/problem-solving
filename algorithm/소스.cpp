#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;

int counter = 0;
vector<int> discovered;
set<int> cutVertex;

//here�� ��Ʈ�� �ϴ� ����Ʈ���� �ִ� ���������� ã�´�
//��ȯ��: �ش� ����Ʈ������ (������) �������� �� �� �ִ� ���� �� ���� ���� �߰ߵ� ������ �߰� ����
//ó�� ȣ���� ���� isRoot = true�̴�
int findCutVertex(int here, bool isRoot) {
	discovered[here] = counter++;
	int ret = discovered[here];

	//here�� ���д� Ʈ���� ��Ʈ�� ��� ������ ������ ���� �ڼ� ����Ʈ���� ���� ����
	int children = 0;
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if (discovered[there] == -1) {
			++children;

			//�� ����Ʈ������ �� �� �ִ� ���� ���� �߰ߵ� ������ �߰� ����
			int subtree = findCutVertex(there, false);

			//�� ��尡 here �Ʒ��� �ִٸ� ���� ��ġ�� �������� �ȴ�
			if (!isRoot && subtree >= discovered[here]) {
				cutVertex.insert(here);
			}
			else ret = min(ret, subtree);
		}
		else ret = min(ret, discovered[there]);
	}

	//here�� ���д� Ʈ���� ��Ʈ�� ��� ������ ����
	if (isRoot && children >= 2) cutVertex.insert(here);

	return ret;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int V, E;
	cin >> V >> E;

	adj = vector<vector<int>>(V, vector<int>(0));
	discovered = vector<int>(V, -1);

	for (int i = 0; i < E; ++i) {
		int u, v;
		cin >> u >> v;

		adj[u - 1].push_back(v - 1);
		adj[v - 1].push_back(u - 1);
	}

	for (int i = 0; i < V; ++i) {
		if(discovered[i] == -1)
			findCutVertex(i, true);
	}

	cout << cutVertex.size()<<"\n";
	for (auto it = cutVertex.begin(); it != cutVertex.end(); ++it)
		cout << *it + 1 << " ";
	return 0;
}