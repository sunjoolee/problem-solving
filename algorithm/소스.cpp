#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_V = 100;

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
//�׷����� ���� ����Ʈ (����� ���� ��ȣ, ���� ����ġ) �� ����
vector<pair<int, double>> adj[MAX_V];

//�־��� �׷����� ���� �ּ� ���д� Ʈ�� ����ġ�� ���� ��ȯ�Ѵ�.
double kruskal() {
	double ret = 0;

	//<����ġ, <u, v>>�� ����� ��´�
	vector<pair<double, pair<int, int>>> edges;
	for (int u = 0; u < V; ++u) {
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i].first;
			double cost = adj[u][i].second;
			edges.push_back({ cost, {u, v} });
		}
	}
	//����ġ������ ����
	sort(edges.begin(), edges.end());

	//ó���� ��� ������ ���� �и��Ǿ� �ִ�.
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); ++i) {
		double cost = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;

		//���� (u, v)�� �˻��Ѵ�.
		//�̹� u�� v�� ����Ǿ����� ���(����Ŭ) ����
		if (sets.find(u) == sets.find(v)) continue;

		sets.merge(u, v);
		ret += cost;
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//���� ����
	cin >> V;

	//���� ��ǥ
	vector<pair<double, double>> stars;
	
	for (int i = 0; i < V; ++i) {
		double x, y;
		cin >> x >> y;
		stars.push_back({ x, y });
	}

	//�׷��� ����
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			double dist  = sqrt(pow(stars[i].first - stars[j].first, 2) + pow(stars[i].second - stars[j].second, 2));

			adj[i].push_back({ j, dist });
			adj[j].push_back({ i, dist });
		}
	}

	cout << kruskal();

	return 0;
}