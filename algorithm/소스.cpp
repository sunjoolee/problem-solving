#include <iostream>
#include <vector>
#include  <algorithm>
using namespace std;

typedef long long ll;
const int MAX_V = 100;
const ll INF = 987654321;

//회의 참석자 수 
int V;
//그래프의 인접 행렬 표현
//정방향 가중치
ll adj[MAX_V][MAX_V];

//플로이드-와샬 알고리즘
void floyd() {
	for (int i = 0; i < V; ++i) {
		adj[i][i] = 0LL; 
	}

	//i지점 -> j지점으로 이동할 때 거쳐가는 지점 K
	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//adj 초기화
	for (int i = 0; i < MAX_V; ++i) {
		for (int j = 0; j < MAX_V; ++j) {
			adj[i][j] = INF;
		}
	}

	//참석자 사이 관계 수
	int M;
	cin >> V >> M;

	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;

		//양방향
		adj[a - 1][b - 1] = min(adj[a - 1][b - 1], 1LL);
		adj[b - 1][a - 1] = min(adj[b - 1][a - 1], 1LL);
	}

	floyd();

	//위원회의 수
	int groupCnt = 0;

	//group[참석자] = 소속된 위원회 번호 (소속되지 않은 경우 -1)
	int group[MAX_V];

	//maxTime[참석자] = 참석자가 위원회 대표일 경우 최대 의사전달시간
	ll maxTime[MAX_V];

	//배열 초기화
	for (int i = 0; i < MAX_V; ++i) {
		group[i] = maxTime[i] = -1;
	}

	//아는 사이 같은 위원회에 속하도록 묶기
	for (int i = 0; i < V; ++i) {
		//소속된 위원회 없는 경우 위원회 생성
		if (group[i] == -1) {
			groupCnt++;
			group[i] = groupCnt;
		}

		for (int j = 0; j < V; ++j) {
			//경로 존재하는 경우 아는 사이 -> 같은 위원회 소속
			if (adj[i][j] < INF) {
				group[j] = group[i];

				//최대 의사전달시간 계산
				maxTime[i] = max(maxTime[i], adj[i][j]);
			}
		}

	}
	cout << groupCnt << "\n";

	//위원회 대표 추출
	vector<int> vec;
	for (int n = 1; n <= groupCnt; ++n) {
		int minPerson;
		ll minTime = INF;

		for (int i = 0; i < V; ++i) {
			if (group[i] != n) continue;
			
			if (minTime > maxTime[i]) {
				minTime = maxTime[i];
				minPerson = i;
			}
		}
		vec.push_back(minPerson);
	}

	sort(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << "\n";

	return 0;
}