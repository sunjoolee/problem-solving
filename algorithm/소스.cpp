#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <algorithm>
using namespace std;

//��Ʈ��ũ ���� ������ �ذ��ϴ� ����-��Ŀ�� �˰����� ����

const int MAX_V = 210;
const int INF = 987654321;
int V;

//cost[u][v] = u���� v�� �����°� ��� ���
//capacity[u][v] = u���� v�� ���� �� �ִ� �뷮
//flow[u][v] = u���� v�� �귯���� ���� (�ݴ� ������ ��� ����)
int cost[MAX_V][MAX_V], capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

//flow[]�� ����ϰ� �� ������ �� ����� ��ȯ�Ѵ�.
int networkFlow(int source, int sink) {
	
	//flow�� 0���� �ʱ�ȭ�Ѵ�.
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	
	while (true) {
		//BFS�� ���� ��θ� ã�´�
		vector<int> parent(MAX_V, -1);
		queue<int> q;

		parent[source] = source;
		q.push(source);

		while (!q.empty() && parent[sink] == -1) {
			int here = q.front();
			q.pop();

			for (int there = 0; there < V; ++there) {
				//�ܿ� �뷮�� �����ִ� ���� Ž��
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}

		//���� ��ΰ� ���� ��� ����
		if (parent[sink] == -1) break;
		
		//���� ��θ� ���� ������ �󸶳� ������ �����Ѵ�
		int amount = INF;
		for (int p = sink; p != source; p = parent[p]) {
			int r = capacity[parent[p]][p] - flow[parent[p]][p];
			amount = min(r, amount);
		}
		//���� ��θ� ���� ������ ������
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}

	return totalFlow;
}


//�׷��� ����
//source 0��
//���� 1�� ~ M��
//��� 1+M�� ~ M + N��
//sink M + N + 1��

//��� ��, ���� ��
int N, M;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	//���� �� = ��� �� + ���� �� + source + sink
	V = N + M + 2;

	//cost, capacity INF�� �ʱ�ȭ
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			cost[i][j] = capacity[i][j] = INF;
		}
	}

	//����� �����ϰ� ���� å�� ��
	//= ��� -> sink ������ �뷮
	for (int i = 0; i < N; ++i) {
		cin >> capacity[1 + M + i][M+N+1];
		cost[1 + M + i][M + N + 1] = 0;
	}
	//������ ������ �ִ� å�� ��
	//= source -> ���� ������ �뷮
	for (int i = 0; i < M; ++i) {
		cin >> capacity[0][1 + i];
		cost[0][1 + i] = 0;
	}

	//���� i -> ��� j �� ������ ��ۺ�
	//= ���� i -> ��� j�� ������ ���
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> cost[1+i][1+M+j];
		}
	}

	cout << networkFlow(0,M+N+1);

	return 0;
}