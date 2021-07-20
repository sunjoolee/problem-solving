#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


const int MAXN = 500;
int n;

//�ǹ��� ���µ� �ɸ��� �ð�
int buildTime[MAXN + 1] = { 0 };
//�ǹ��� �ϼ��� �ð�
int finishTime[MAXN];

int inDegree[MAXN+1] = { 0 };
//vector<int> child[i]: �ǹ�i�� �������� �ϴ� �ǹ����� ����
vector<int> child[MAXN+1];
//vector<int> parent[i]: �ǹ�i�� �����ؾ� �ϴ� �ǹ����� ����
vector<int> parent[MAXN + 1];

void topologySort() {
	int res = 0;

	queue<int> q;

	for (int i = 1; i <= n; ++i) {
		if (inDegree[i] == 0) q.push(i);
		finishTime[i] = buildTime[i];
	}

	for (int i = 1; i <= n; ++i) {
		//n���� ������ �湮�ϱ� ���� ť�� �������� ����Ŭ�� �߻��� ��
		if (q.empty()) return;

		int parentnode = q.front();
		q.pop();

		for (int i = 0; i < child[parentnode].size(); ++i) {
			int childnode = child[parentnode][i];
			
			if (--inDegree[childnode] == 0) {
				q.push(childnode);

				int maxTime = 0;
				for (auto it = parent[childnode].begin(); it != parent[childnode].end(); ++it)
					maxTime = max(maxTime, finishTime[*it]);
				finishTime[childnode] = maxTime + buildTime[childnode];
			}
		}
	}

	return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> buildTime[i];

		while (true) {
			int parentnode;
			cin >> parentnode;
			if (parentnode == -1) break;

			child[parentnode].push_back(i);
			parent[i].push_back(parentnode);
			inDegree[i]++;
		}
	}

	topologySort();

	for (int i = 1; i <= n; ++i)
		cout << finishTime[i] << "\n";

	return 0;
}