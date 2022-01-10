#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_V = 100;

//크루스칼 최소 스패닝 트리 알고리즘
//트리를 이용해 상호 배타적 집합을 구현한다

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
vector<pair<int, double>> adj[MAX_V];

//주어진 그래프에 대해 최소 스패닝 트리 가중치의 합을 반환한다.
double kruskal() {
	double ret = 0;

	//<가중치, <u, v>>의 목록을 얻는다
	vector<pair<double, pair<int, int>>> edges;
	for (int u = 0; u < V; ++u) {
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i].first;
			double cost = adj[u][i].second;
			edges.push_back({ cost, {u, v} });
		}
	}
	//가중치순으로 정렬
	sort(edges.begin(), edges.end());

	//처음엔 모든 정점이 서로 분리되어 있다.
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); ++i) {
		double cost = edges[i].first;
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

	//별의 개수
	cin >> V;

	//별의 좌표
	vector<pair<double, double>> stars;
	
	for (int i = 0; i < V; ++i) {
		double x, y;
		cin >> x >> y;
		stars.push_back({ x, y });
	}

	//그래프 생성
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