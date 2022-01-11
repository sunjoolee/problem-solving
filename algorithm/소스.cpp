#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAX_V = 100000;

//�༺ ����ü
struct Planet {
	ll x, y, z;
	Planet(ll x, ll y, ll z) : x(x), y(y), z(z) {};
};


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

//�༺�� ����
int V;

//�༺�� ��� ����
vector<Planet> planets;

//�־��� �༺�鿡 ���� �ּ� ���д� Ʈ�� ����ġ�� ���� ��ȯ
ll kruskalPlanets() {
	ll ret = 0LL;

	//<����ġ, <u, v>>�� ��� = u��° �༺�� v��° �༺ ������ �Ÿ�
	vector<pair<ll, pair<int, int>>> edges;

	for (int u = 0; u < V; ++u) {
		Planet uPlanet = planets[u];

		//����� �����̹Ƿ� ��� (u, v)���� ����ġ�� ������� �ʾƵ� ��
		for (int v = u; v < V; ++v) {
			Planet vPlanet = planets[v];
			
			ll dist = min(abs(uPlanet.x - vPlanet.x), min(abs(uPlanet.y - vPlanet.y), abs(uPlanet.z - vPlanet.z)));
			edges.push_back({ dist, {u, v} });
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

		sets.merge(u, v);
		ret += cost;
	}

	return ret;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> V;
	
	for (int i = 0; i < V; ++i) {
		ll x, y, z;
		cin >> x >> y >> z;
		
		planets.push_back(Planet(x, y, z));
	}

	cout << kruskalPlanets();

	return 0;
}