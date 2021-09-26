#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;

int counter = 0;
vector<int> discovered;
set<int> cutVertex;

//here을 루트로 하는 서브트리에 있는 절단점들을 찾는다
//반환값: 해당 서브트리에서 (역방향) 간선으로 갈 수 있는 정점 중 가장 일찍 발견된 정점의 발견 시점
//처음 호출할 때는 isRoot = true이다
int findCutVertex(int here, bool isRoot) {
	discovered[here] = counter++;
	int ret = discovered[here];

	//here가 스패닝 트리의 루트인 경우 절단점 판정을 위해 자손 서브트리의 개수 저장
	int children = 0;
	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if (discovered[there] == -1) {
			++children;

			//이 서브트리에서 갈 수 있는 가장 일찍 발견된 정점의 발견 시점
			int subtree = findCutVertex(there, false);

			//그 노드가 here 아래에 있다면 현재 위치는 절단점이 된다
			if (!isRoot && subtree >= discovered[here]) {
				cutVertex.insert(here);
			}
			else ret = min(ret, subtree);
		}
		else ret = min(ret, discovered[there]);
	}

	//here가 스패닝 트리의 루트인 경우 절단점 판정
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