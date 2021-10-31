#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>
using namespace std;

const int MAX_V = 10000;

//������ ����
int V, E;

//�׷����� ���� ����Ʈ 
//adj[u]: <u�� �������� ����� ���� v, ������ ����ġ w> ���� 
vector<pair<int, double>> adj[MAX_V];

//���ͽ�Ʈ���� �ִ� �Ÿ� �˰��� 
double dijkstra(int start) {
	vector<double> dist(V, -1);
	dist[start] = 1;

	//pq: <-���������� �Ÿ�, ������ ��ȣ> ����
	priority_queue<pair<double, int>> pq;
	pq.push(make_pair(-1, start));

	while (!pq.empty()) {
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		//cost���� ª�� ��ΰ� �̹� �߰ߵǾ��ٸ� ����
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
		//�ʱ�ȭ
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