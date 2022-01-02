#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

const int MAX_V = 500 + 1;
const ll INF = 987654321;
const ll OCHA = 125751501; //501^3

//������ ����
int V;

//�׷����� ���� ����Ʈ <����� ���� ��ȣ, ������ ����ġ>
vector<pair<int, ll>> adj[MAX_V];


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
					updated = true;
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

	int TC;
	cin >> TC;
	while (TC--) {
		//�׷��� �ʱ�ȭ
		for (int i = 0; i < MAX_V; ++i){
			adj[i].clear();
		}
		
		int M, W;

		cin >> V >> M >> W;

		//�ٸ� �Է� �ޱ�
		for(int i = 0; i < M; ++i) {
			int S, E;
			ll T;
			cin >> S >> E >> T;

			adj[S].push_back({ E, T });
			adj[E].push_back({ S, T });
		}
		//��Ȧ �Է� �ޱ�
		for (int i = 0; i < W; ++i) {
			int S, E;
			ll T;
			cin >> S >> E >> T;

			adj[S].push_back({ E, -T });
		}

		//1�� ���ÿ� ����� ������ ���� ����
		V++;
		adj[0].push_back({ 1, 0 });
		adj[1].push_back({ 0, 0 });

		vector<ll> res = bellmanFord(0);

		if (res.empty()) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}