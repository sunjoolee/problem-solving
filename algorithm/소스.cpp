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


//end의 최단 거리를 반환하는 bfs
int bfs(int n, int startnode, int endnode) {
	
	vector<int> dist(n, INF);
	vector<int> visited(n, 0);
	
	//<node, 거리>
	queue <pair<int, int>> q;
	q.push({ startnode, 0 });

	while (!q.empty()) {
		int curnode = q.front().first;
		int curcost = q.front().second;
		q.pop();

		if (!isTrap[curnode] && visited[curnode] == 1) continue;
		visited[curnode] = 1;

		if (isTrap[curnode]) {
			vector<pair<int, int>> tmp(adj[curnode].begin(), adj[curnode].end());

			adj[curnode].clear();
			adj[curnode].assign(reverseAdj[curnode].begin(), reverseAdj[curnode].end());

			reverseAdj[curnode].clear();
			reverseAdj[curnode].assign(tmp.begin(), tmp.end());
		}
			
		for (int i = 0; i < adj[curnode].size(); ++i) {
			int nextnode = adj[curnode][i].first;
			int nextcost = curcost + adj[curnode][i].second;

			if (isTrap[nextnode]) {
				q.push({ nextnode, nextcost });
			}
				
			else if (visited[nextnode] == 0 || dist[nextnode] > nextcost){
				dist[nextnode] = nextcost;
				q.push({ nextnode, nextcost });
			}	
		}
		
	}
	return dist[endnode];
}

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {

	Groads = roads;
	Gtraps = traps;

	for (int i = 0; i < roads.size(); ++i) {
		vector<int> edge = roads[i];

		int u = edge[0] - 1; 
		int v = edge[1] - 1; 
		int cost = edge[2];

		adj[u].push_back({ v, cost }); 
		reverseAdj[v].push_back({ u, cost });
	}

	for (int i = 0; i < traps.size(); ++i) {
		isTrap[traps[i] - 1] = true;
	}

	int answer = bfs(n, start - 1, end - 1);

	return answer;
}