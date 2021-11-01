#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, H, W, M, K;

//���� 
int map[500][500];

//���� ��ġ ǥ�� ����
int unit_map[500][500];

int dir_R[4] = { 0, 0, 1, -1 };
int dir_C[4] = { 1, -1, 0, 0 };

//���ص� ���� ���� 
vector<int> NN;

//����
struct unit {
	int m;
	int t;
	pair<int, int> location;
};

//���� ���� ����
vector<unit> MM;

//���ͽ�Ʈ���� �ִ� �Ÿ� �˰��� 
void dijkstra(int u, pair<int, int> goal) {

	//��ǥ ���� �̵� �Ұ����� ������ ��� ����
	if (NN[map[goal.first][goal.second] - 1] == -1) return;

	//��ǥ ������ ������ �ִ� ��� ����
	if (unit_map[goal.first][goal.second] != -1) return;

	//������ ����
	unit& start = MM[u - 1];

	int dist[500][500];
	//�ʱ�ȭ
	for (int i = 0; i < 500; ++i) {
		for (int j = 0; j < 500; ++j) {
			dist[i][j] = -1;
		}
	}
	dist[start.location.first][start.location.second] = 0;

	//pq: <-��ǥ������ �Ÿ�, ��ǥ> ����
	priority_queue<pair<int, pair<int, int>>> pq;
	pq.push({0, start.location});

	while (!pq.empty()) {
		int cost = -pq.top().first;
		pair<int, int> here = pq.top().second;
		pq.pop();

		//cost���� ª�� ��ΰ� �̹� �߰ߵǾ��ٸ� ����
		if (dist[here.first][here.second] != -1 && dist[here.first][here.second] < cost) continue;

		//������ ������ ������ �ƴ� ���
		//������ ĭ�� �� ������ �ִ� ��� ����
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

		//���� ĭ���� �̵�
		for (int i = 0; i < 4; ++i) {
			pair<int, int> there = { here.first + dir_R[i], here.second + dir_C[i] };

			if (there.first < 0 || there.first >= H) continue;
			if (there.second < 0 || there.second >= W) continue;

			//�ٸ� ������ ������ �ִ� ��� ����
			if (unit_map[there.first][there.second] != -1 && unit_map[there.first][there.second] != start.t) continue;

			//�ʹ� �����Ͽ� �̵��� �� ���� ��� ����
			int next_cost = NN[map[there.first][there.second] - 1];
			if (next_cost == -1) continue;

			//�̵����� �Ѱ�� �̵��� �� ���� ��� ����
			int nextDist = cost + next_cost;
			if (nextDist > start.m) continue;

			if (dist[there.first][there.second] == -1 || dist[there.first][there.second] > nextDist) {
				dist[there.first][there.second] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}

	//���ͽ�Ʈ�� �� ������ ������ �����ߴ��� �˻�
	if (dist[goal.first][goal.second] != -1) {
		//������ ��� ���� �̵�
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

	//�ʱ�ȭ
	for (int i = 0; i < 500; ++i) {
		for (int j = 0; j < 500; ++j) {
			map[i][j] = -1;
			unit_map[i][j] = -1;
		}
	}

	cin >> N >> H >> W;
	
	//���� �Է� �ޱ�
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			cin >> map[i][j];
		}
	}
	//���ص� �Է� �ޱ�
	for (int i = 0; i < N; ++i) {
		int input;
		cin >> input;
		NN.push_back(input);
	}

	//���� �Է� �ޱ�
	cin >> M;
	for (int i = 0; i < M; ++i) {
		int m, t, a, b;
		cin >> m >> t >> a >> b;
		MM.push_back({ m, t, {a, b} });

		//���� ��ġ ���� ������ ǥ��
		unit_map[a][b] = t;
	}

	//���� ��� �Է� �ޱ�
	cin >> K;
	while (K--) {
		int u, a, b;
		cin >> u >> a >> b;
		dijkstra(u, { a, b });
	}

	//��� ���
	for (int i = 0; i < M; ++i) {
		cout << MM[i].location.first << " " << MM[i].location.second << "\n";
	}

	return 0;
}