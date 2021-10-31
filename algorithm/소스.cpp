#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_N = 100000;

int N, M, K, S, p, q;

//safe[i]: i�� ���ð� �����ϸ� 1, �����ϸ� 0, ���� �����̸� -1 
vector<int> safe(MAX_N, 1);

//�׷����� ���� ����Ʈ ǥ��
vector<int> adj[MAX_N];

//BFS -> ������ ���� ���ϱ�
void BFS(int start) {
	vector<int> visited(N, 0);
	queue<pair<int, int>> q;
	q.push({ start, 0 });

	while (!q.empty()) {
		int here = q.front().first;
		int depth = q.front().second;
		q.pop();

		if (visited[here] == 1 || depth > S) continue;

		//���� ���÷κ��� S�� ������ �̵����� �̵� ����
		visited[here] = 1;
		if(safe[here] != -1) safe[here] = 0;

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i];
			if (visited[there] == 0) 
				q.push({there, depth + 1});
		}
	}
}

//���ͽ�Ʈ�� -> 0 ~ N-1 �ִ� ��� ���ϱ� 
void dijkstra() {
	vector<long long> dist(N, -1);
	dist[0] = 0;

	//pq: <-���������� �Ÿ�, ������ ��ȣ> ����
	priority_queue<pair<long long, int>> pq;
	pq.push(make_pair(0, 0));

	while (!pq.empty()) {
		long long cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		//cost���� ª�� ��ΰ� �̹� �߰ߵǾ��ٸ� ����
		if (dist[here] != -1 && dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); ++i) {
			long long nextDist = cost;
			int there = adj[here][i];
			
			//���� ���ɵ� ���ø� �ǳʶٱ�
			if (safe[there] == -1) continue;
			//������ ���ø� ���ں� p
			if (safe[there] == 1) nextDist += p;
			//������ ���ø� ���ں� q
			if (safe[there] == 0) nextDist += q;

			if (dist[there] == -1 || dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}

	//N-1��° ���ÿ����� ������ �ʿ�X
	//N-1�� ������ ���ñ����� ��� �� �ִ� ���� ���
	for (int i = 0; i < adj[N - 1].size(); ++i) {
		int adjacent = adj[N - 1][i];
		dist[N - 1] = min(dist[N - 1], dist[adjacent]);
	}

	cout << dist[N - 1];
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);

	cin >> N >> M >> K >> S >> p >> q;

	//���� ���� ����
	vector<int> zombie;
	for (int i = 0; i < K; ++i) {
		int input;
		cin >> input;
		
		zombie.push_back(input - 1);
		safe[input - 1] = -1;
	}

	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;

		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}

	for (int i = 0; i < zombie.size(); ++i) BFS(zombie[i]);
	
	dijkstra();
	return 0;
}