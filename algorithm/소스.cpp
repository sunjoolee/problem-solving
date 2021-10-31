#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>
using namespace std;

int N, K;

//다익스트라의 최단 거리 알고리즘 
 int dijkstra(int start, int end) {
	vector<int> dist(100001, -1);
	dist[start] = 0;

	//pq: <-위치까지 걸리는 시간, 위치> 저장
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, start));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		//cost보다 짧은 경로가 이미 발견되었다면 무시
		if (dist[here] != -1 && dist[here] < cost) continue;

		if (here + 1 <= 100000) {
			int there = here + 1;
			if (dist[there] == -1 || dist[there] > cost + 1) {
				dist[there] = cost + 1;
				pq.push(make_pair(-(cost + 1), there));
			}
		}
		
		if (here - 1 >= 0) {
			int there = here - 1;
			if (dist[there] == -1 || dist[there] > cost + 1) {
				dist[there] = cost + 1;
				pq.push(make_pair(-(cost + 1), there));
			}
		}

		if (here * 2 <= 100000) {
			int there = here * 2;
			if (dist[there] == -1 || dist[there] > cost) {
				dist[there] = cost;
				pq.push(make_pair(-cost, there));
			}

		}
	}
	return dist[K];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);

	cin >> N >> K;

	cout << dijkstra(N, K);

	return 0;
}