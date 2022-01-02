#include <iostream>
#include  <algorithm>
using namespace std;

typedef long long ll;
const int MAX_V = 100;
const ll INF = 987654321;

//정점의 개수 
int V;
//그래프의 인접 행렬 표현
//adj[u][v] = u에서 v로 가는 간선의 가중치
ll adj[MAX_V][MAX_V];

//플로이드-와샬 알고리즘
void floyd() {
	for (int i = 0; i < V; ++i) 
		adj[i][i] = 0LL;

	//i지점 -> j지점으로 이동할 때 거쳐가는 지점 K
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//adj 초기화
	for (int i = 0; i < MAX_V; ++i)
		for (int j = 0; j < MAX_V; ++j)
			adj[i][j] = INF;

	//버스의 개수
	int E;
	cin >> V >> E;

	for (int i = 0; i < E; ++i) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		
		adj[a-1][b-1] = min(adj[a-1][b-1], c);
	}

	floyd();

	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			if (adj[i][j] < INF) cout << adj[i][j] << " ";
			else cout << "0 ";
		}
		cout << "\n";
	}

	return 0;
}