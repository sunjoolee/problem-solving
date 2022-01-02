#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

const int MAX_V = 500;
const ll INF = 987654321;
const ll OCHA = 250000;

//������ ����
int V;
//������ ����
int E;

//�׷����� ���� ����Ʈ <����� ���� ��ȣ, ������ ����ġ>
vector<pair<int, ll>> adj[MAX_V];

//0�� ���ÿ� ����� �������� üũ
vector<int> connected(MAX_V, 0);

void bfs() {
	queue<int> q;
	q.push(0);

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		if (connected[here]) break;
		connected[here] = 1;

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			if (!connected[there]) q.push(there);
		}
	}
}

//���� ����Ŭ�� ���� ��� �� �� �迭 ��ȯ
//���� ���� src
vector<ll> bellmanFord(int src) {
	//�������� ������ ��� ���������� �ִ� �Ÿ� ���� INF
	vector<ll> upper(V, INF);
	upper[src] = 0;
	bool updated;

	//V�� ��ȸ
	for (int iter = 0; iter < V; ++iter) {
		updated = false;
		for (int here = 0; here < V; ++here) {
			for (int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].first;
				ll cost = adj[here][i].second;

				//(here, there)������ ���� ��ȭ �õ�
				if (upper[there] > upper[here] + cost) {
					//����
					upper[there] = upper[here] + cost;

					//0�� ���ÿ� ����� ������ ��� ��ȭ üũ
					if(connected[there]) updated = true;
				}
			}
		}
		//��� ������ ���� ��ȭ�� �������� ��� V-1�� �� �ʿ� ���� ���� ����
		if (!updated) break;
	}
	//V��° ��ȸ���� ��ȭ�� �����ߴٸ� ���� ����Ŭ ����
	if (updated) upper.clear();

	return upper;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> V >> E;

	for (int i = 0; i < E; ++i) {
		int A, B;
		ll C;
		cin >> A >> B >> C;

		adj[A - 1].push_back({ B - 1, C });
	}

	//0�� ���ÿ� ����� ���� üũ
	bfs();

	vector<ll> res = bellmanFord(0);
	
	if (res.empty()) cout << -1;
	else {
		for (int i = 1; i < res.size(); ++i) {
			if (res[i] < INF - OCHA) cout << res[i] << "\n";
			else cout << -1 << "\n";
		}
	}

	return 0;
}