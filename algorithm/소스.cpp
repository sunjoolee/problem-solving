#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const int MAXN = 2097152 + 5; // = 2^21  + 5

//트리 높이, 트리 노드 수
int k, n;
//<왼쪽 서브트리와 연결하는 간선의 가중치, 오른쪽 서브트리와 연결하는 간선의 가중치 >
vector<pair<ull, ull>> edge (MAXN, make_pair(0,0));

//노드 방문
int visited[MAXN];
//toLeaf[i]: 노드 i ~ 리프 거리의 최댓값
ull toLeaf[MAXN] = { 0 };

//toLeaf[] 계산 
ull getToLeaf(int curnode) {
	visited[curnode] = 1;

	ull maxdist = 0;

	//왼쪽 서브트리
	if ((curnode * 2 <= n) && (visited[curnode * 2] == 0)) {
		if (edge[curnode].first > 0)
			maxdist = max(maxdist, edge[curnode].first + getToLeaf(curnode * 2));
	}
	//오른쪽 서브트리
	if ((curnode * 2 + 1 <= n) && (visited[curnode * 2 + 1] == 0)) {
		if (edge[curnode].second > 0)
			maxdist = max(maxdist, edge[curnode].second + getToLeaf(curnode * 2 + 1));
	}

	toLeaf[curnode] = maxdist;
	return maxdist;
}

//루트 노드에서부터 간선의 가중치 변화
void addWeight(int curnode, int maxdist) {
	visited[curnode] = 1;

	//왼쪽 서브트리
	if ((curnode * 2 <= n) && (visited[curnode * 2] == 0)) {
		if (edge[curnode].first > 0) {
			//기존 간선의 가중치 = (루트~리프 거리의 최댓값 - 왼쪽 서브트리~리프 거리의 최댓값)
			edge[curnode].first = (maxdist - toLeaf[curnode * 2]);

			//재귀 호출 -> 왼쪽 서브트리의 간선 가중치 조정
			addWeight(curnode * 2, maxdist - edge[curnode].first);
		}
	}
	//오른쪽 서브트리
	if ((curnode * 2 + 1 <= n) && (visited[curnode * 2 + 1] == 0)) {
		if (edge[curnode].second > 0) {
			//기존 간선의 가중치 = (루트~리프 거리의 최댓값 - 오른쪽 서브트리~리프 거리의 최댓값)
			edge[curnode].second = (maxdist - toLeaf[curnode * 2 + 1]);

			//재귀 호출 -> 오른쪽 서브트리의 간선 가중치 조정
			addWeight(curnode * 2 + 1, maxdist - edge[curnode].second);
		}	
	}

	return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> k;

	n = pow(2, k + 1) - 1;
	
	//리프 노드 제외 노드들의 간선의 가중치 입력받기
	for (int i = 1; i <= n - pow(2, k); ++i) {
		int w1, w2;
		cin >> w1 >> w2;

		edge[i] = make_pair(w1, w2);
	}

	//노드 ~ 리프 거리의 최댓값 toLeaf[] 계산
	memset(visited, 0, sizeof(visited));
	getToLeaf(1);

	//루트와 가까운 간선부터 가중치 조정
	//루트 ~ 리프 거리의 최댓값: toLeaf[루트]
	memset(visited, 0, sizeof(visited));
	addWeight(1, toLeaf[1]);

	//트리의 간선의 가중치의 합 계산
	ull sum = 0;
	for (int i = 1; i <= n; ++i) {
		sum += edge[i].first;
		sum += edge[i].second;
	}
	cout << sum;

	return 0;
}