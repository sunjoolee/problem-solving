#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 987654321;

//roads의 행은 [P, Q, S]로 이루어져 있습니다.
//P에서 Q로 갈 수 있는 길이 있으며, 길을 따라 이동하는데 S만큼 시간이 걸립니다.
vector<vector<int>> Groads;
//함정 노드
vector<int> Gtraps;

//adj[u] = {v, cost} u -cost-> v
vector<vector<pair<int, int>>> adj(1000, vector<pair<int, int>>());

//reverseAdj[u] = {v, cost} u <-cost- v
vector<vector<pair<int, int>>> reverseAdj(1000, vector<pair<int, int>>());

vector<bool> isTrap(1000, false);

//최단 거리를 구하기 위한 다익스트라 알고리즘
int dijkstra(int n, int start, int end) {
	
	vector<int> dist(n, INF);
	vector<int> reverseDist(n, INF);
	
	bool reversed = false;
	dist[start] = 0;

	//<<-cost, usedTrap>, node>
	priority_queue<pair<pair<int,bool>, int>> pq;
	pq.push({ {0, false }, start});

	while (!pq.empty()) {
		int cost = -pq.top().first.first;
		bool hereReversed = pq.top().first.second;
		int here = pq.top().second;
		pq.pop();

		if (!hereReversed && cost > dist[here]) continue;
		if (hereReversed && cost > reverseDist[here]) continue;

		//인접한 정점들을 모두 검사한다.
		if (!isTrap[here]) {
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int nextDist = cost + adj[here][i].second;

				//더 짧은 경로를 발견한 경우, dist[]를 갱신하고 우선순위 큐에 넣는다.
				if (!hereReversed && dist[there] > nextDist) {
						dist[there] = nextDist;
						pq.push({ {-nextDist, false}, there });
				}
				//더 짧은 경로를 발견한 경우, reverseDist[]를 갱신하고 우선순위 큐에 넣는다.
				else if (reverseDist[there] > nextDist) {
						reverseDist[there] = nextDist;
						pq.push({ {-nextDist, false}, there });
				}
			}
		}
		else{
			for (int i = 0; i < reverseAdj[here].size(); i++) {
				int there = reverseAdj[here][i].first;
				int nextDist = cost + reverseAdj[here][i].second;

				//더 짧은 경로를 발견한 경우, reverseDist[]를 갱신하고 우선순위 큐에 넣는다.
				if (!hereReversed && reverseDist[there] > nextDist) {
					reverseDist[there] = nextDist;
					pq.push({ {-nextDist, true}, there });
				}
				//더 짧은 경로를 발견한 경우, dist[]를 갱신하고 우선순위 큐에 넣는다.
				else if (dist[there] > nextDist) {
					dist[there] = nextDist;
					pq.push({ {-nextDist, true}, there });
				}
			}
		}
	}
	return min(dist[end], reverseDist[end]);
}

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {

	Groads = roads;
	Gtraps = traps;

	for (int i = 0; i < roads.size(); ++i) {
		vector<int> edge = roads[i];

		int u = edge[0]; 
		int v = edge[1]; 
		int cost = edge[2];

		adj[u].push_back({ v, cost }); 
		reverseAdj[v].push_back({ u, cost });
	}

	for (int i = 0; i < traps.size(); ++i) {
		isTrap[traps[i]] = true;
	}

	int answer = dijkstra(n, start, end);

	return answer;
}