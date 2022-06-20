#include <algorithm>
#include <queue>
#include <set>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAXN = 18;

//bfs를 위한 그래프
vector<vector<int>> adj(vector<vector<int>>(MAXN, vector<int>()));


//info 0: 양, 1: 늑대, 2: 현재 위치, -1: 빈 노드(=방문한 노드)
const int SHEEP = 0;
const int WOLF = 1;
const int VISITED = -1;

int bfs(vector<int> info) {

	//중복된 상태 진입 방지 <curNode, curInfo>
	set<pair<int, vector<int>>> visited;

	//<<curNode, <curSheep, curWolf>>, info>
	queue<pair<pair<int, pair<int, int>>, vector<int>>> q;

	//bfs 무조건 0번 노드(info[0] = 0)부터 시작
	info[0] = VISITED;
	q.push({ {0, {1, 0}}, info });

	int answer = 1;
	while (!q.empty()) {
		int curNode = q.front().first.first;
		int curSheep = q.front().first.second.first;
		int curWolf = q.front().first.second.second;
		vector<int> curInfo = q.front().second;
		q.pop();

		if (visited.find({ curNode, curInfo }) != visited.end()) continue;
		visited.insert({ curNode, curInfo });

		answer = max(answer, curSheep);

		cout << curNode <<" " << curSheep << " " << curWolf << "\n";

		for (int i = 0; i < adj[curNode].size(); ++i) {
				int nextNode = adj[curNode][i];
				int nextSheep = curSheep;
				int nextWolf = curWolf;
				
				if (curInfo[nextNode] == SHEEP) {
					nextSheep++;
				}
				else if (curInfo[nextNode] == WOLF) {
					nextWolf++;
				}
				//curInfo[nextNode] == VISITED 인 경우 no action

				//이동할 수 없는 노드인 경우
				if (nextWolf >= nextSheep) continue;

				//다음 이동할 노드 큐에 넣기
				int tmp = curInfo[nextNode];
				curInfo[nextNode] = VISITED;
				if (visited.find({ nextNode, curInfo }) == visited.end()) {
					q.push({ {nextNode, {nextSheep, nextWolf}}, curInfo });
				}
				curInfo[nextNode] = tmp;
		}
	}
	return answer;
}

int solution(vector<int> info, vector<vector<int>> edges) {
	for (int i = 0; i < edges.size(); ++i) {
		int parent = edges[i][0];
		int child = edges[i][1];

		adj[parent].push_back(child);
		adj[child].push_back(parent);
	}

	int answer = bfs(info);
	return answer;
}

int main() {
	solution({ 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0 }, { {0, 1},{0, 2},{1, 3},{1, 4},{2, 5},{2, 6},{3, 7},{4, 8},{6, 9},{9, 10} });
}