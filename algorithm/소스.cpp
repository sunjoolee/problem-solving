#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

const int MAX_V = 50;

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
vector<pair<int, int>> adj[MAX_V];

//주어진 그래프에 대해 최소 스패닝 트리 가중치의 합을 반환한다.
int kruskal() {
	int ret = 0;

	//<가중치, <u, v>>의 목록을 얻는다
	vector<pair<int, pair<int, int>>> edges;

	for (int u = 0; u < V; ++u) {
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i].first;
			int cost = adj[u][i].second;
			edges.push_back({ cost, {u, v} });
		}
	}
	//가중치순으로 정렬
	sort(edges.begin(), edges.end());

	//처음엔 모든 정점이 서로 분리되어 있다.
	DisjointSet sets(V);

	for (int i = 0; i < edges.size(); ++i) {
		int cost = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;

		//간선 (u, v)를 검사한다.
		//이미 u와 v가 연결되어있을 경우(사이클) 무시
		if (sets.find(u) == sets.find(v)) continue;

		sets.merge(u, v);
		ret += cost;
	}

	//모든 컴퓨터 연결 확인
	bool connected = true;
	for (int i = 0; i < V; ++i) {
		//모두 하나의 집합에 있다면 모두 같은 parent를 갖는다
		if (sets.find(i) != sets.find(0)) {
			connected = false;
			break;
		}
	}

	if (!connected) return -1;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//알파벳 숫자 매핑
	map<char, int> alphaToNum;
	for (int i = 0; i < 26; ++i) {
		char alpha = 97 + i; //소문자
		char alpha2 = 65 + i; //대문자

		alphaToNum[alpha] = i + 1;
		alphaToNum[alpha2] = i + 27;
	}

	cin >> V;
	int totalLen = 0;

	for (int i = 0; i < V; ++i) {
		string input;
		cin >> input;

		for (int j = 0; j < V; ++j) {
			
			//간선 존재하지 않는 경우
			if (input[j] == '0') continue;

			int len = alphaToNum[input[j]];
			totalLen += len;

			adj[i].push_back({ j, len });
		}
	}
	
	int res = kruskal();

	if (res == -1) cout << "-1";
	else cout << totalLen - res;

	return 0;
}