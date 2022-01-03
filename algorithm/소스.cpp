#include <iostream>
#include  <algorithm>
using namespace std;

typedef long long ll;
const int MAX_V = 400;
const ll INF = 987654321;

//정점의 개수 
int V;
//그래프의 인접 행렬 표현
//정방향 가중치
ll adj[MAX_V][MAX_V];
//역방향 가중치
ll adjOpposite[MAX_V][MAX_V];

//플로이드-와샬 알고리즘
void floyd() {
	for (int i = 0; i < V; ++i) {
		adj[i][i] = 0LL; 
		adjOpposite[i][i] = 0LL;
	}

	//i지점 -> j지점으로 이동할 때 거쳐가는 지점 K
	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
				adjOpposite[i][j] = min(adjOpposite[i][j], adjOpposite[i][k] + adjOpposite[k][j]);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//adj 초기화
	for (int i = 0; i < MAX_V; ++i) {
		for (int j = 0; j < MAX_V; ++j) {
			adj[i][j] = INF;
			adjOpposite[i][j] = INF;
		}
	}

	//전후관계의 수
	int k;
	cin >> V >> k;

	for (int i = 0; i < k; ++i) {
		int a, b;
		cin >> a >> b;

		adj[a-1][b-1] = min(adj[a-1][b-1], 1LL);
		adjOpposite[b-1][a-1] = min(adj[b-1][a-1], 1LL);
	}

	floyd();

	//알고 싶은 쌍의 개수
	int s;
	cin >> s;
	
	for (int i = 0; i < s; ++i) {
		int a, b;
		cin >> a >> b;

		//정방향 경로 존재
		if (adj[a - 1][b - 1] < INF) cout << "-1\n";
		//역빙향 경로 존재
		else if (adjOpposite[a - 1][b - 1] < INF) cout << "1\n";
		//정방향 경로와 역방향 경로 둘다 존재하지 않음
		else cout << "0\n";
	}
	

	return 0;
}