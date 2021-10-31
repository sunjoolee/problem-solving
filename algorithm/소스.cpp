#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>
using namespace std;

const int MAX_V = 10000;

//정점의 개수
int V, E;

//그래프의 인접 리스트 
//adj[u]: <u와 간선으로 연결된 정점 v, 간선의 가중치 w> 저장 
vector<pair<int, double>> adj[MAX_V];

//다익스트라의 최단 거리 알고리즘 
double dijkstra(int start) {
	vector<double> dist(V, -1);
	dist[start] = 1;

	//pq: <-정점까지의 거리, 정점의 번호> 저장
	priority_queue<pair<double, int>> pq;
	pq.push(make_pair(-1, start));

	while (!pq.empty()) {
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		//cost보다 짧은 경로가 이미 발견되었다면 무시
		if (dist[here] != -1 && dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			double nextDist = adj[here][i].second * cost;

			if (dist[there] == -1 || dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist[V-1];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);

	int c;
	cin >> c;
	while (c--) {
		//초기화
		for(int i = 0; i < MAX_V; ++i)
			adj[i].clear();

		cin >> V >> E;

		for (int i = 0; i < E; ++i) {
			int a, b; double c;
			cin >> a >> b >> c;

			adj[a].push_back(make_pair(b, c));
			adj[b].push_back(make_pair(a, c));
		}
		
		cout << fixed;
		cout.precision(10);
		cout << dijkstra(0) << "\n";
	}

	return 0;
}