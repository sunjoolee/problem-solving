#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

const int MAX_V = 500 + 1;
const ll INF = 987654321;
const ll OCHA = 125751501; //501^3

//정점의 개수
int V;

//그래프의 인접 리스트 <연결된 정점 번호, 간선의 가중치>
vector<pair<int, ll>> adj[MAX_V];


//음수 사이클이 있을 경우 텅 빈 배열 반환
//시작 정점 src
vector<ll> bellmanFord(int src) {
	//시작점을 제외한 모든 정점까지의 최단 거리 상한 INF
	vector<ll> upper(V, INF);
	upper[src] = 0;

	bool updated;

	//V번 순회
	for (int iter = 0; iter < V; ++iter) {
		updated = false;
		for (int here = 0; here < V; ++here) {
			for (int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].first;
				ll cost = adj[here][i].second;

				//(here, there)간선을 따라 완화 시도
				if (upper[there] > upper[here] + cost) {
					//성공
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		}
		//모든 간선에 대해 완화가 실패했을 경우 V-1번 돌 필요 없이 곧장 종료
		if (!updated) break;
	}
	//V번째 순회에도 완화가 성공했다면 음수 사이클 존재
	if (updated) upper.clear();

	return upper;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int TC;
	cin >> TC;
	while (TC--) {
		//그래프 초기화
		for (int i = 0; i < MAX_V; ++i){
			adj[i].clear();
		}
		
		int M, W;

		cin >> V >> M >> W;

		//다리 입력 받기
		for(int i = 0; i < M; ++i) {
			int S, E;
			ll T;
			cin >> S >> E >> T;

			adj[S].push_back({ E, T });
			adj[E].push_back({ S, T });
		}
		//웜홀 입력 받기
		for (int i = 0; i < W; ++i) {
			int S, E;
			ll T;
			cin >> S >> E >> T;

			adj[S].push_back({ E, -T });
		}

		//1번 도시와 연결된 가상의 시작 지점
		V++;
		adj[0].push_back({ 1, 0 });
		adj[1].push_back({ 0, 0 });

		vector<ll> res = bellmanFord(0);

		if (res.empty()) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}