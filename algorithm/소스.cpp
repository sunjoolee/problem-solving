
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 10;
int n;
//inDegree[i]: 정점i에 들어가는 간선의 수
int inDegree[MAXN] = { 0 };
//vector<int> child[i]: 노드i를 선행 노드로 하는 노드들의 집합
vector<int> child[MAXN];
//위상 정렬 함수
void topologySort() {
	int result[MAXN];
	queue<int> q;
	//진입 차수 0인 정점 큐에 삽입
	for (int i = 1; i <= n; ++i)
		if (inDegree[i] == 0) q.push(i);
	//정렬이 완전히 수행되기까지 n개의 정점을 방문한다
	for (int i = 1; i <= n; ++i) {
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
	for (int i = 1; i <= n; ++i)
		cout << result[i] << " ";
	return;
}
int main() {
	//정점의 수
	n = 7;
	//간선 추가
	//child[parent].push_back(child);
	//inDegree[child]++;
	child[1].push_back(2);
	inDegree[2]++;
	child[1].push_back(5);
	inDegree[5]++;
	child[2].push_back(3);
	inDegree[3]++;
	child[3].push_back(4);
	inDegree[4]++;
	child[4].push_back(6);
	inDegree[6]++;
	child[5].push_back(6);
	inDegree[6]++;
	child[6].push_back(7);
	inDegree[7]++;
	topologySort();
	return 0;
}