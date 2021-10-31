#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_N = 100000;

int N, M, K, S, p, q;

//safe[i]: i번 도시가 안전하면 1, 위험하면 0, 좀비 점령이면 -1 
vector<int> safe(MAX_N, 1);

//그래프의 인접 리스트 표현
vector<int> adj[MAX_N];

//BFS -> 위험한 도시 구하기
void BFS(int start) {
	vector<int> visited(N, 0);
	queue<pair<int, int>> q;
	q.push({ start, 0 });

	while (!q.empty()) {
		int here = q.front().first;
		int depth = q.front().second;
		q.pop();

		if (visited[here] == 1 || depth > S) continue;

		//좀비 도시로부터 S번 이하의 이동으로 이동 가능
		visited[here] = 1;
		if(safe[here] != -1) safe[here] = 0;

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i];
			if (visited[there] == 0) 
				q.push({there, depth + 1});
		}
	}
}

//다익스트라 -> 0 ~ N-1 최단 경로 구하기 
void dijkstra() {
	vector<long long> dist(N, -1);
	dist[0] = 0;

	//pq: <-정점까지의 거리, 정점의 번호> 저장
	priority_queue<pair<long long, int>> pq;
	pq.push(make_pair(0, 0));

	while (!pq.empty()) {
		long long cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		//cost보다 짧은 경로가 이미 발견되었다면 무시
		if (dist[here] != -1 && dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); ++i) {
			long long nextDist = cost;
			int there = adj[here][i];
			
			//좀비 점령된 도시면 건너뛰기
			if (safe[there] == -1) continue;
			//안전한 도시면 숙박비 p
			if (safe[there] == 1) nextDist += p;
			//위험한 도시면 숙박비 q
			if (safe[there] == 0) nextDist += q;

			if (dist[there] == -1 || dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}

	//N-1번째 도시에서는 숙박할 필요X
	//N-1과 인접한 도시까지의 경로 중 최단 길이 출력
	for (int i = 0; i < adj[N - 1].size(); ++i) {
		int adjacent = adj[N - 1][i];
		dist[N - 1] = min(dist[N - 1], dist[adjacent]);
	}

	cout << dist[N - 1];
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);

	cin >> N >> M >> K >> S >> p >> q;

	//좀비 점령 도시
	vector<int> zombie;
	for (int i = 0; i < K; ++i) {
		int input;
		cin >> input;
		
		zombie.push_back(input - 1);
		safe[input - 1] = -1;
	}

	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;

		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}

	for (int i = 0; i < zombie.size(); ++i) BFS(zombie[i]);
	
	dijkstra();
	return 0;
}