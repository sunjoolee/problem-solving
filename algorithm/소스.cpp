#include<iostream>
#include<cstring>
#include <algorithm>

using namespace std;

const int MAX = 16;
const int INF = 987654321;

int N;
int W[MAX][MAX];
//cost[node][bitmask]: 현재 노드에서 지금까지 방문한 노드의 집합 bitmask일 때의 최소 비용
int cost[MAX][1 << MAX];

int TSP(int node, int bitmask)
{	
	//base case: 모든 노드 방문 완료
	//다시 원래의 도시로 돌아올 수 있어야 한다
	if (bitmask == ((1 << N) - 1)){
		//현재 노드와 0번 노드 사이 연결되어있지 않은 경우
		if (W[node][0] == 0) 
			return INF;
		else 
			return W[node][0];
	}

	//매모이제이션
	int& ret = cost[node][bitmask];
	if (ret != -1) return ret;

	ret = INF;
	for (int i = 0; i < N; i++){
		//현재 노드와 i번 노드 사이 연결되어있지 않은 경우 건너뛰기
		if (W[node][i] == 0) continue;
		//i번 노드 이미 방문했을 경우 건너뛰기
		if (bitmask & (1 << i)) continue;

		ret = min(ret, W[node][i] + TSP(i, bitmask | (1 << i)));
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	memset(cost, -1, sizeof(cost));

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> W[i][j];

	//0번째 도시부터 순회 시작
	//0번째 도시만 표시된 bitmask = 00..001
	cout << TSP(0, 1);

	return 0;
}
