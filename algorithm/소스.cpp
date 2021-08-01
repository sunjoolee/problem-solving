#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


//adj[i] : 노드i와 인접한 노드 집합
vector<int> adj[200000];

//visited[i] : 노드 i가 bfs에 의해 방문된 횟수
//(adj[i].size() / 2)번 이상 방문되면 루머를 믿기 시작한다
int visited[200000] = { 0 };

//belive[i]: 노드 i가 루머를 믿기 시작한 시간
int believe[200000];

//<현재 노드 위치, 현재 시간>
//루머를 믿기 시작하면 노드 큐에 저장
queue<pair<int, int>> q;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 200000; ++i)
		believe[i] = -1;

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		while (true) {
			int input;
			cin >> input;
			if (input == 0) break;

			adj[i].push_back(input - 1);
		}
	}


	//최초 유포자
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int input;
		cin >> input;
		q.push(make_pair(input - 1, 0));
	}

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		int curnode = cur.first;
		int curtime = cur.second;
		q.pop();

		//자신이 루머를 믿기 시작한 시간 갱신
		if (believe[curnode] != -1) continue;
		believe[curnode] = curtime;

		//자신의 주변 노드에 루머 퍼트리기
		for (int i = 0; i < adj[curnode].size(); ++i) {
			int adjnode = adj[curnode][i];

			if (believe[adjnode] == -1) {
				visited[adjnode]++;
				if (visited[adjnode] >= ((double)adj[adjnode].size() / 2)) {
					q.push(make_pair(adjnode, curtime + 1));
				}
			}
		}
	}
	
	for (int i = 0; i < n; ++i)
		cout << believe[i] << " ";

	return 0;
}