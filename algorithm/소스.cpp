#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//<연결된 노드, 연결하는 간선의 다이너마이트 수>
vector<pair<int, int>> edge[1001];
//노드 방문 여부
int visited[1001];

int getMinCost(int curnode, int curcost) {

	//노드 방문 표시
	visited[curnode] = 1;
	
	//리프 노드인 경우 
	//최소 다이너마이트 개수 = 자신의 간선의 다이너마이트 수
	if (curnode != 1 && edge[curnode].size() == 1)
		return curcost;

	//리프 노드 아닌 경우
	//1. 자식 노드들의 최소 다이너마이트 개수의 합 계산
	int sum = 0;
	for (int i = 0; i < edge[curnode].size(); ++i) {
		int nextnode = edge[curnode][i].first;
		int nextcost = edge[curnode][i].second;

		if (nextnode != 1 && visited[nextnode] == 0)
			sum += getMinCost(nextnode, nextcost);
	}
	//2. min(자신의 간선의 다이너마이트 수, 자식 노드들의 최소 다이너마이트 개수의 합)
	return min(curcost, sum);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		//초기화
		for (int i = 0; i < 1001; ++i) {
			edge[i].clear();
			visited[i] = 0;
		}

		int n, m;
		cin >> n >> m;

		//섬 하나 뿐인 경우
		if (n == 1) {
			cout << 0;
			continue;
		}

		for (int i = 0; i < m; ++i) {
			int a, b, d;
			cin >> a >> b >> d;

			edge[a].push_back(make_pair(b, d));
			edge[b].push_back(make_pair(a, d));
		}
		
		//루트 노드 1과 연결된 간선에 대해 각각 계산
		int ans = 0;
		for (int i = 0; i < edge[1].size(); ++i) {
			int firstnode = edge[1][i].first;
			int firstcost = edge[1][i].second;
			ans += getMinCost(firstnode, firstcost);
		}

		cout << ans << "\n";
	}

	return 0;
}