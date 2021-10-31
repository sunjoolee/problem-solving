#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>
using namespace std;

int N, K;

//���ͽ�Ʈ���� �ִ� �Ÿ� �˰��� 
 int dijkstra(int start, int end) {
	vector<int> dist(100001, -1);
	dist[start] = 0;

	//pq: <-��ġ���� �ɸ��� �ð�, ��ġ> ����
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, start));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		//cost���� ª�� ��ΰ� �̹� �߰ߵǾ��ٸ� ����
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