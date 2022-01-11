#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAX_V = 100000;

//행성 구조체
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

	//u가 속한 트리의 루트 번호 반환
	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	//u가 속한 트리와 v가 속한 트리를 합친다
	void merge(int u, int v) {
		u = find(u); v = find(v);

		//u와 v가 이미 같은 트리에 속하는 경우 걸러냄
		if (u == v) return;

		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) ++rank[v];
	}
};

//행성의 개수
int V;

//행성의 목록 저장
vector<Planet> planets;

//주어진 행성들에 대해 최소 스패닝 트리 가중치의 합을 반환
ll kruskalPlanets() {
	ll ret = 0LL;

	//<가중치, <u, v>>의 목록 = u번째 행성과 v번째 행성 사이의 거리
	vector<pair<ll, pair<int, int>>> edges;

	for (int u = 0; u < V; ++u) {
		Planet uPlanet = planets[u];

		//양방향 간선이므로 모든 (u, v)쌍의 가중치를 계산하지 않아도 됨
		for (int v = u; v < V; ++v) {
			Planet vPlanet = planets[v];
			
			ll dist = min(abs(uPlanet.x - vPlanet.x), min(abs(uPlanet.y - vPlanet.y), abs(uPlanet.z - vPlanet.z)));
			edges.push_back({ dist, {u, v} });
		}
	}
	//가중치순으로 정렬
	sort(edges.begin(), edges.end());

	//처음엔 모든 정점이 서로 분리되어 있다.
	DisjointSet sets(V);

	for (int i = 0; i < edges.size(); ++i) {
		ll cost = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;

		//간선 (u, v)를 검사한다.
		//이미 u와 v가 연결되어있을 경우(사이클) 무시
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