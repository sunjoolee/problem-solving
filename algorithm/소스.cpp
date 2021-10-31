#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_N = 1001;
int N, M;

//�׷����� ���� ����Ʈ ǥ��
//adj[u]: <u�� �������� ����� ���� v, ������ ����ġ w>
vector<pair<int, int>> adj[MAX_N];

//���� ��ǻ��(= 0�� ��ǻ��)���� ���ͽ�Ʈ�� Ž��
void dijkstra() {
	vector<int> dist(N, -1);
	dist[0] = 0;

	//���ͽ�Ʈ�� ���д� Ʈ��
	vector<int> parent(N, -1);
	parent[0] = 0;

	//pq: <-���������� �Ÿ�, ������ ��ȣ> ����
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, 0));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		//cost���� ª�� ��ΰ� �̹� �߰ߵǾ��ٸ� ����
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

	//���ͽ�Ʈ�� ���д� Ʈ�� ���
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