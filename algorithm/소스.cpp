#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;

int counter = 0;
vector<int> discovered;
set<pair<int, int>> bridge;

//��ȯ��: �ش� ����Ʈ������ (������) �������� �� �� �ִ� ���� �� ���� ���� �߰ߵ� ������ �߰� ����
//ó�� ȣ���� ���� parent = -1�̴�
int findBridge(int here, int parent) {
	discovered[here] = counter++;
	int ret = discovered[here];

	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];

		//�ڽ��� �θ�� ���� ���� ����
		if (there == parent) continue;

		if (discovered[there] == -1) {
			//there�� ��Ʈ�� �ϴ� ����Ʈ������ �� �� �ִ� ���� ���� �߰ߵ� ������ �߰� ����
			int subtree = findBridge(there, here);

			//�� ��尡 here �Ʒ��� �ִٸ� ����(here, there)�� �ٸ��̴�
			if (subtree > discovered[here]) {
				if (here < there) bridge.insert({ here, there });
				else bridge.insert({ there, here });
			}
			else ret = min(ret, subtree);
		}
		else ret = min(ret, discovered[there]);
	}
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

	findBridge(0, -1);

	cout << bridge.size() << "\n";
	for (auto it = bridge.begin(); it != bridge.end(); ++it)
		cout << it->first + 1 << " " << it->second + 1 << "\n";

	return 0;
}