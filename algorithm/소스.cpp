#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n, s, d;

//간선
vector<int> edge[100001];

//노드 방문 여부
int visited[100001];

//toLeaf[i]: 노드 i ~ 리프 노드까지의 최대 깊이
int toLeaf[100001] = { 0 };

//오토바이가 이동한 거리(편도)
int path = 0;

int getToLeaf(int curnode) {
	
	//노드 방문 표시
	visited[curnode] = 1;

	//자식 노드 없을 경우 리프 노드까지의 최대 깊이 = 0
	int maxdep = 0;

	for (int i = 0; i < edge[curnode].size(); ++i) {
		int nextnode = edge[curnode][i];

		if (visited[nextnode] == 0)
			maxdep = max(maxdep, 1 + getToLeaf(nextnode));
	}
	
	toLeaf[curnode] = maxdep;
	return maxdep;
}

void moveMotorcycle(int curnode) {

	//노드 방문 표시
	visited[curnode] = 1;

	//DFS
	for (int i = 0; i < edge[curnode].size(); ++i) {
		int nextnode = edge[curnode][i];

		if (visited[nextnode] == 0) {
			//toLeaf > d인 경우 오토바이가 이동
			if (toLeaf[nextnode] >= d) path++;

			moveMotorcycle(nextnode);
		}
	}

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> s >> d;

	for (int i = 1; i < n; ++i) {
		int x, y;
		cin >> x >> y;

		edge[x].push_back(y);
		edge[y].push_back(x);
	}

	//힘 = 0인 경우 모든 간선을 다 이동해야한다
	if (d == 0){
		cout << 2 * (n - 1);
		return 0;
	}

	memset(visited, 0, sizeof(visited));
	getToLeaf(s);

	memset(visited, 0, sizeof(visited));
	moveMotorcycle(s);

	//오토바이가 이동한 거리(왕복)
	cout << 2 * path;

	return 0;
}