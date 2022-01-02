#include <iostream>
#include  <algorithm>
using namespace std;

const int MAX_V = 500;

//정점의 개수 
int V;
//그래프의 인접 행렬 표현
//adj[u][v] = u에서 v로 가는 간선의 가중치
int adj[MAX_V][MAX_V];

//플로이드-와샬 알고리즘
void floyd() {
	for (int i = 0; i < V; ++i) 
		adj[i][i] = 0;

	//i지점 -> j지점으로 이동할 때 거쳐가는 지점 K
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	return 0;
}