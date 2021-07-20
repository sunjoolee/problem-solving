#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


const int MAXN = 500;
int n;

//건물을 짓는데 걸리는 시간
int buildTime[MAXN + 1] = { 0 };
//건물이 완성된 시간
int finishTime[MAXN];

int inDegree[MAXN+1] = { 0 };
//vector<int> child[i]: 건물i를 선행으로 하는 건물들의 집합
vector<int> child[MAXN+1];
//vector<int> parent[i]: 건물i가 선행해야 하는 건물들의 집합
vector<int> parent[MAXN + 1];

void topologySort() {
	int res = 0;

	queue<int> q;

	for (int i = 1; i <= n; ++i) {
		if (inDegree[i] == 0) q.push(i);
		finishTime[i] = buildTime[i];
	}

	for (int i = 1; i <= n; ++i) {
		//n개의 정점을 방문하기 전에 큐가 비어버리면 사이클이 발생한 것
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