#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;

//inDegree[i]: 정점i에 들어가는 간선의 수
vector<int> inDegree;
//child[i]: 노드i를 선행 노드로 하는 노드들의 집합
vector<vector<int>> child;

//위상 정렬 함수
void topologySort() {

	vector<int> result(n, 0);
	queue<int> q;

	//진입 차수 0인 정점 큐에 삽입
	for (int i = 0; i < n; ++i)
		if (inDegree[i] == 0) q.push(i);
	
	//정렬이 완전히 수행되기까지 n개의 정점을 방문한다
	for (int i = 0; i < n; ++i) {
		//n개의 정점을 방문하기 전에 큐가 비어버리면 
		//사이클이 발생한 것이다
		if (q.empty()) return;

		//진입 차수가 0인 정점 선택
		int parent = q.front();
		result[i] = parent;

		//선택된 정점과 여기에 부속된 모든 간선들 삭제
		q.pop();
		for (int i = 0; i < child[parent].size(); ++i) {
			int childnode = child[parent][i];
			//새롭게 진입차수가 0이 된 정점을 큐에 삽입
			if (--inDegree[childnode] == 0)
				q.push(childnode);
		}
	}

	//위상 정렬 결과 출력
	for (int i = 0; i < n; ++i)
		cout << result[i] + 1 << " ";

	return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;

	inDegree = vector<int>(n, 0);
	child = vector<vector<int>> (n, vector<int>(0));

	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;

		child[u-1].push_back(v - 1);
		inDegree[v - 1]++;
	}

	topologySort();
	return 0;
}