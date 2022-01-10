#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAX_V = 301;

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

//정점의 개수
int V;

//그래프의 인접 리스트 (연결된 정점 번호, 간선 가중치) 쌍 저장
vector<pair<int, ll>> adj[MAX_V];

//주어진 그래프에 대해 최소 스패닝 트리 가중치의 합을 반환한다.
ll kruskal() {
	ll ret = 0LL;

	//<가중치, <u, v>>의 목록을 얻는다
	vector<pair<ll, pair<int, int>>> edges;

	for (int u = 0; u < V; ++u) {
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i].first;
			ll cost = adj[u][i].second;
			edges.push_back({ cost, {u, v} });
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
	
	//간선의 개수
	int M;
	//케이블의 개수
	int K;

	cin >> V;
	
	//입력으로 주어지는 논 1~N번
	//논에 직접 우물을 파는 경우 연결할 가상의 정점 0번
	//따라서 총 정점의 개수 = N + 1
	V++;

	//논에 우물을 팔 때 드는 비용
	for (int i = 1; i < V; ++i) {
		ll w;
		cin >> w;

		adj[i].push_back({ 0, w });
		adj[0].push_back({ i, w });
	}

	//다른 논으로부터 물을 끌어오는 경우
	for (int i = 1; i < V; ++i) {
		for(int j = 1; j < V; ++j) {
			ll p;
			cin >> p;

			adj[i].push_back({ j, p });
		}
	}

	cout << kruskal();

	return 0;
}