#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory.h>
#include <map>
#include <algorithm>
using namespace std;

//��Ʈ��ũ ���� ������ �ذ��ϴ� ����-��Ŀ�� �˰����� ����

//������ �ִ� ���� = ������ ũ�� NxM
const int MAX_V = 10000;
const int INF = 987654321;
int V;

//capacity[u][v] = u���� v�� ���� �� �ִ� �뷮
//flow[u][v] = u���� v�� �귯���� ���� (�ݴ� ������ ��� ����)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];


int networkFlow(int source, int sink) {
	
	//---------------------------------
	//����-��Ŀ�� �˰��� 


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

	//---------------------------------
	//�ִ� �뷮 �ִ� ���� ����

	//source�� ���� ���������Ͽ� bfs�� �Ͽ� S�� ���Ѵ�

	//bfs ���� visited[����] = 1 ��� �� ������ S�� ���Եǰ�
	//visited[����] = 0 ��� �� ������ T�� ���Եȴ�

	vector<int> visited(V, 0);
	queue<int> qq;

	qq.push(source);

	while (!qq.empty()) {
		int here = qq.front();
		qq.pop();

		if (visited[here] == 1) continue;

		visited[here] = 1;

		for (int there = 0; there < V; ++there) {
			if (capacity[here][there] != 0 && visited[there] == 0) {
				//here -> there ������ �ܿ� �뷮 ���
				int r = capacity[here][there] - flow[here][there];
				
				//here = source�� ��� ������ �ܿ� �뷮 �ִٰ� ����
				if (here == source || r > 0) {
					qq.push(there);
				}
			}
		}
	}

	//��S,T�� �뷮 = S->T�� �����ϴ� �������� �뷮�� ���� ���Ѵ�
	int totalCapacity = 0;
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			if (visited[i] == 1 && visited[j] == 0) {
				totalCapacity += capacity[i][j];
			}
		}
	}

	return totalCapacity;
}

//���� ũ��
int R, W;

//������ ��ǥ ����� ���� �迭
const int rDir[4] = { 1, -1, 0, 0 };
const int wDir[4] = { 0, 0, 1, -1 };

bool inRange(int r, int w) {
	if (r < 0 || r >= R) return false;
	if (w < 0 || w >= W) return false;
	return true;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> R >> W;

	//����
	vector<string> map;

	//��ǥ[r][w]�� i��ȣ = id[r][w]
	//�̵��� �� ���� ��ǥ�� ��� -1
	vector<vector<int>> id(100, vector<int>(100, -1));

	//�����̿� �б��� ���̵�
	int sId, tId;

	for (int i = 0; i < R; ++i) {
		string input;
		cin >> input;
		map.push_back(input);

		//�� ĭ�� ��ȸ�ϸ� ��ȣ�� �ű��
		for (int j = 0; j < W; ++j) {
			if (map[i][j] != '#') id[i][j] = V++;

			if (map[i][j] == 'K') sId = id[i][j];
			if (map[i][j] == 'H') tId = id[i][j];
		}
	}


	//capacity�� 0���� �ʱ�ȭ�Ѵ�.
	memset(capacity, 0, sizeof(capacity));

	//�׷��� �𵨸�
	//��� ĭ�� ���� ������ ĭ 
	for (int i1 = 0; i1 < R; ++i1) {
		for (int j1 = 0; j1 < W; ++j1) {
			if (map[i1][j1] != '#') {
				for (int k = 0; k < 4; ++k) {
					int i2 = i1 + rDir[k];
					int j2 = j1 + wDir[k];
					if (inRange(i2, j2) && map[i2][j2] != '#') {
						//�����, ����ġ 1
						capacity[id[i1][j1]][id[i2][j2]] = 1;
						capacity[id[i2][j2]][id[i1][j1]] = 1;
					}
				}
			}
		}
		
	}

	//���� -> ������ �б� ������ ���
	if (capacity[sId][tId] != 0) {
		cout << -1;
		return 0;
	}


	cout << networkFlow(sId, tId);

	return 0;
}