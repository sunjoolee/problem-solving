#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
//그래프 인접 리스트 표현
vector<vector<int>> adj;

//start부터 너비 우선 탐색하여 방문하는 정점 수
int bfs(int start) {
	int cnt = 0;
	queue<int> q;
	vector<int> found(N, 0);

	q.push(start);
	found[start] = 1;

	while (!q.empty()) {
		int here = q.front();
		cnt++;
		q.pop();

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i];

			if (found[there] == 0) {
				q.push(there);
				found[there] = 1;
			}
		}
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	
	adj = vector<vector<int>>(N, vector<int>(0));

	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;

		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}
	 
	cout << bfs(0) - 1;
	return 0;
}