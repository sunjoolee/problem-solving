#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, H, W, M, K;

//지도 
int map[500][500];

//유닛 위치 표시 지도
int unit_map[500][500];

int dir_R[4] = { 0, 0, 1, -1 };
int dir_C[4] = { 1, -1, 0, 0 };

//험준도 저장 벡터 
vector<int> NN;

//유닛
struct unit {
	int m;
	int t;
	pair<int, int> location;
};

//유닛 저장 벡터
vector<unit> MM;

//다익스트라의 최단 거리 알고리즘 
void dijkstra(int u, pair<int, int> goal) {

	//목표 지점 이동 불가능한 지형인 경우 종료
	if (NN[map[goal.first][goal.second] - 1] == -1) return;

	//목표 지점에 유닛이 있는 경우 종료
	if (unit_map[goal.first][goal.second] != -1) return;

	//약진할 유닛
	unit& start = MM[u - 1];

	int dist[500][500];
	//초기화
	for (int i = 0; i < 500; ++i) {
		for (int j = 0; j < 500; ++j) {
			dist[i][j] = -1;
		}
	}
	dist[start.location.first][start.location.second] = 0;

	//pq: <-좌표까지의 거리, 좌표> 저장
	priority_queue<pair<int, pair<int, int>>> pq;
	pq.push({0, start.location});

	while (!pq.empty()) {
		int cost = -pq.top().first;
		pair<int, int> here = pq.top().second;
		pq.pop();

		//cost보다 짧은 경로가 이미 발견되었다면 종료
		if (dist[here.first][here.second] != -1 && dist[here.first][here.second] < cost) continue;

		//약진을 시작한 시점이 아닌 경우
		//인접한 칸에 적 유닛이 있는 경우 종료
		bool flag = false;
		if (here.first != start.location.first || here.second != start.location.second) {
			for (int i = 0; i < 4; ++i) {
				pair<int, int> adj = { here.first + dir_R[i], here.second + dir_C[i] };

				if (adj.first < 0 || adj.first >= H) continue;
				if (adj.second < 0 || adj.second >= W) continue;

				if (unit_map[adj.first][adj.second] != -1 && unit_map[adj.first][adj.second] != start.t) {
					flag = true;
					break;
				}
			}
		}
		if (flag) continue;

		//다음 칸으로 이동
		for (int i = 0; i < 4; ++i) {
			pair<int, int> there = { here.first + dir_R[i], here.second + dir_C[i] };

			if (there.first < 0 || there.first >= H) continue;
			if (there.second < 0 || there.second >= W) continue;

			//다른 세력의 유닛이 있는 경우 무시
			if (unit_map[there.first][there.second] != -1 && unit_map[there.first][there.second] != start.t) continue;

			//너무 험준하여 이동할 수 없는 경우 무시
			int next_cost = NN[map[there.first][there.second] - 1];
			if (next_cost == -1) continue;

			//이동력의 한계로 이동할 수 없는 경우 무시
			int nextDist = cost + next_cost;
			if (nextDist > start.m) continue;

			if (dist[there.first][there.second] == -1 || dist[there.first][there.second] > nextDist) {
				dist[there.first][there.second] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}

	//다익스트라 후 유닛이 약진에 성공했는지 검사
	if (dist[goal.first][goal.second] != -1) {
		//성공한 경우 유닛 이동
		unit_map[start.location.first][start.location.second] = -1;
		start.location.first = goal.first;
		start.location.second = goal.second; 
		unit_map[start.location.first][start.location.second] = start.t;
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//초기화
	for (int i = 0; i < 500; ++i) {
		for (int j = 0; j < 500; ++j) {
			map[i][j] = -1;
			unit_map[i][j] = -1;
		}
	}

	cin >> N >> H >> W;
	
	//지도 입력 받기
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			cin >> map[i][j];
		}
	}
	//험준도 입력 받기
	for (int i = 0; i < N; ++i) {
		int input;
		cin >> input;
		NN.push_back(input);
	}

	//유닛 입력 받기
	cin >> M;
	for (int i = 0; i < M; ++i) {
		int m, t, a, b;
		cin >> m >> t >> a >> b;
		MM.push_back({ m, t, {a, b} });

		//유닛 위치 유닛 지도에 표시
		unit_map[a][b] = t;
	}

	//약진 명령 입력 받기
	cin >> K;
	while (K--) {
		int u, a, b;
		cin >> u >> a >> b;
		dijkstra(u, { a, b });
	}

	//결과 출력
	for (int i = 0; i < M; ++i) {
		cout << MM[i].location.first << " " << MM[i].location.second << "\n";
	}

	return 0;
}