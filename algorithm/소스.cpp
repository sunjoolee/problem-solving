#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_N = 1001;
int N, M;

//그래프의 인접 리스트 표현
//adj[u]: <u와 간선으로 연결된 정점 v, 간선의 가중치 w>
vector<pair<int, int>> adj[MAX_N];

//슈퍼 컴퓨터(= 0번 컴퓨터)부터 다익스트라 탐색
void dijkstra() {
	vector<int> dist(N, -1);
	dist[0] = 0;

	//다익스트라 스패닝 트리
	vector<int> parent(N, -1);
	parent[0] = 0;

	//pq: <-정점까지의 거리, 정점의 번호> 저장
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, 0));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		//cost보다 짧은 경로가 이미 발견되었다면 무시
		if (dist[here] != -1 && dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = adj[here][i].second + cost;

			if (dist[there] == -1 || dist[there] > nextDist) {
				dist[there] = nextDist;
				parent[there] = here;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}

	//다익스트라 스패닝 트리 출력
	int cnt = 0;
	for (int i = 0; i < N; ++i) {
		if (parent[i] != i && parent[i] != -1) cnt++;
	}
	cout << cnt << "\n";
	for (int i = 0; i < N; ++i) {
		if (parent[i] != i && parent[i] != -1)
			cout << i << " " << parent[i] << "\n";
	}
	return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int A, B, C;
		cin >> A >> B >> C;

		adj[A - 1].push_back({ B - 1, C });
		adj[B - 1].push_back({ A - 1, C });
	}

	dijkstra();
	return 0;
}