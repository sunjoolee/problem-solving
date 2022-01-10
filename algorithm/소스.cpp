#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long int ll;
const int MAX_V = 200001;

//ũ�罺Į �ּ� ���д� Ʈ�� �˰���
//Ʈ���� �̿��� ��ȣ ��Ÿ�� ������ �����Ѵ�

struct DisjointSet {
	vector<int> parent, rank;
	DisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}

	//u�� ���� Ʈ���� ��Ʈ ��ȣ ��ȯ
	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	//u�� ���� Ʈ���� v�� ���� Ʈ���� ��ģ��
	void merge(int u, int v) {
		u = find(u); v = find(v);

		//u�� v�� �̹� ���� Ʈ���� ���ϴ� ��� �ɷ���
		if (u == v) return;

		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) ++rank[v];
	}
};

//������ ����
int V;

//������ ������ ��
int M;

//�׷����� ���� ����Ʈ (����� ���� ��ȣ, ���� ����ġ) �� ����
vector<pair<int, ll>> adj[MAX_V];

//�־��� �׷����� ���� �ּ� ���д� Ʈ�� ����ġ�� ���� ��ȯ�Ѵ�.
ll kruskal() {
	ll ret = 0LL;

	//<����ġ, <u, v>>�� ����� ��´�
	vector<pair<ll, pair<int, int>>> edges;

	for (int u = 0; u < V; ++u) {
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i].first;
			ll cost = adj[u][i].second;
			edges.push_back({ cost, {u, v} });
		}
	}
	//����ġ������ ����
	sort(edges.begin(), edges.end());

	//ó���� ��� ������ ���� �и��Ǿ� �ִ�.
	DisjointSet sets(V);

	for (int i = 0; i < edges.size(); ++i) {
		ll cost = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;

		//���� (u, v)�� �˻��Ѵ�.
		//�̹� u�� v�� ����Ǿ����� ���(����Ŭ) ����
		if (sets.find(u) == sets.find(v)) continue;

		//��ġ�� �� �ִ� ������ ���� Ȯ��
		if (u != 0 && v != 0) {
			if (M == 0) continue;
			else M--;
		}
		sets.merge(u, v);
		ret += cost;
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//����: �� ���� ���̸� �����ϴ� ����
	//��� Ż�ⱸ: �ⱸ�� ���ø� �����ϴ� ����

	cin >> V >> M;
	
	// �ⱸ : 0�� ����
	// N���� �� : 1 ~ N�� ����
	// ���� �� ������ �� = N + 1
	V++;

	//���� ����ġ
	for (int i = 0; i < M; ++i) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}

	//��� Ż�ⱸ ����ġ
	for (int i = 1; i < V; ++i) {
		ll t;
		cin >> t;
		adj[0].push_back({ i, t });
		adj[i].push_back({ 0, t });
	}

	cout << kruskal();

	return 0;
}