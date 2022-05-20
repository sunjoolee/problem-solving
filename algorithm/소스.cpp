#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

const int MAXN = 1001;

//건물을 짓는데 걸리는 시간
ll delay[MAXN] = { 0 };

//건물을 짓기 시작하는 시점
ll construct[MAXN] = { 0 };

//inDegree[i]: 정점i에 들어가는 간선의 수
int inDegree[MAXN] = { 0 };

//vector<int> child[i]: 노드i를 선행 노드로 하는 노드들의 집합
vector<int> child[MAXN];


//위상 정렬 함수
int topologySort(int n, int w) {
	
	queue<int> q;

	//진입 차수 0인 정점 큐에 삽입
	for (int i = 1; i <= n; ++i) {
		if (inDegree[i] == 0) q.push(i);
	}

	//정렬이 완전히 수행되기까지 n개의 정점을 방문한다
	for (int i = 1; i <= n; ++i) {

		//n개의 정점을 방문하기 전에 큐가 비어버리면 사이클이 발생한 것
		if (q.empty()) return -1;
		

		//진입 차수가 0인 정점 선택
		int parent = q.front();

		//승리하기 위해 건설해야하는 건물인 경우
		if (parent == w) return construct[w] + delay[w];

		//선택된 정점과 여기에 부속된 모든 간선들 삭제
		q.pop();
		for (int i = 0; i < child[parent].size(); ++i) {
			int childnode = child[parent][i];
			inDegree[childnode]--;

			//child 건물을 짓기 시작하는 시점
			construct[childnode] = max(construct[childnode], construct[parent] + delay[parent]);

			//새롭게 진입차수가 0이 된 정점을 큐에 삽입
			if (inDegree[childnode] == 0) {
				q.push(childnode);
			}
		}
	}
	return -1;
}


int main() {
	
	//테스트 케이스 수
	int t;
	cin >> t;
	while(t--){
		//초기화
		for (int i = 0; i < MAXN; ++i) {
			delay[i] = 0;
			construct[i] = 0;
			inDegree[i] = { 0 };
			child[i].clear();

		}
		//건물 수
		int n;
		cin >> n;
		//건물 규칙 수
		int k;
		cin >> k;

		for (int i = 1; i <= n; ++i) {
			ll d;
			cin >> d;
			delay[i] = d;
		}

		for (int i = 0; i < k; ++i) {
			int x, y;
			cin >> x >> y;
			child[x].push_back(y);
			inDegree[y]++;
		}

		//승리하기 위해 건설해야하는 건물 번호
		int w;
		cin >> w;

		cout << topologySort(n,w) <<"\n";
	}
	return 0;
}