#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory.h>
#include <map>
#include <algorithm>
using namespace std;

const int MAX_V = 40000;
const int INF = 987654321;
int V;

//������ ������ ��Ÿ���� ����ü
struct Edge {
	int target, capacity, flow;

	//������ ������ ������
	Edge* reverse;

	//�� ������ �ܿ� �뷮�� ����Ѵ�
	int residualCapacity() const { return capacity - flow; }

	//�� ������ �̿��� amount�� ������
	void push(int amount) {
		flow += amount;
		reverse->flow -= amount;
	}
};

//���� ��Ʈ��ũ�� ���� ����Ʈ
vector<Edge*> adj[MAX_V];

//u���� v�� ���� ������ �߰��Ѵ�
void addEdge(int u, int v, int capacity) {
	Edge* uv = new Edge();
	Edge* vu = new Edge();

	//u���� v�� ���� ������ �ʱ�ȭ�Ѵ�
	uv->target = v;
	uv->capacity = capacity;
	uv->flow = 0;
	uv->reverse = vu;

	//v���� u�� ���� ������ �ʱ�ȭ�Ѵ� (���� ����)
	vu->target = u;
	vu->capacity = 0;
	vu->flow = 0;
	vu->reverse = uv;

	adj[u].push_back(uv);
	adj[v].push_back(vu);
}


int networkFlow(int source, int sink) {

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

			for (int i = 0; i < adj[here].size(); ++i) {
				Edge* hereToThere = adj[here][i];
				int there = hereToThere->target;

				//�ܿ� �뷮�� �����ִ� ���� Ž��
				if (hereToThere->residualCapacity() > 0 && parent[there] == -1) {
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
			for (int i = 0; i < adj[parent[p]].size(); ++i) {
				Edge* pEdge = adj[parent[p]][i];
				if (pEdge->target == p) {
					amount = min(pEdge->residualCapacity(), amount);
				}
			}
		}

		//���� ��θ� ���� ������ ������
		for (int p = sink; p != source; p = parent[p]) {
			for (int i = 0; i < adj[parent[p]].size(); ++i) {
				Edge* pEdge = adj[parent[p]][i];
				if (pEdge->target == p) {
					pEdge->push(amount);
				}
			}
		}
		totalFlow += amount;
	}

	return totalFlow;
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
	vector<string> city;

	//������ ������ in, out �������� �ɰ���
	//����~���� ���� ���� = ����ġ INF, ����� ����
	//in->out ���� ���� = ����ġ 1, �ܹ��� ����

	//������ ��ȣ ¦�� = ������ ��ǥ�� ��ȣ & ������ ������ ���� in ������ ��ȣ
	//������ ��ȣ Ȧ�� = ������ �������� ������ out ������ ��ȣ
	V = 0;
	vector<vector<int>> id(200, vector<int>(200, -1));

	//������ ��ǥ�� ���̵� ����ϱ�
	int sId;
	//�б��� ��ǥ�� ���̵� ����ϱ�
	int tId;

	for (int i = 0; i < R; ++i) {
		string input;
		cin >> input;
		city.push_back(input);

		//��� ������ ��ǥ�� ��ȸ�ϸ� ������ ��ǥ�� ��ȣ ���̱� 
		//�ش� ��ǥ ������ �ɰ��� in->out ���� �����

		for (int j = 0; j < W; ++j) {
			if (city[i][j] != '#') {
				id[i][j] = V;
				V += 2;

				//in -> out ���� �߰�
				addEdge(id[i][j], id[i][j] + 1, 1);
			}
			if (city[i][j] == 'K') sId = id[i][j];
			if (city[i][j] == 'H') tId = id[i][j];
		}
	}


	//��� ĭ�� ���� ������ ĭ�� ��ȸ�ϸ� ������ �����Ѵ� 
	for (int i1 = 0; i1 < R; ++i1) {
		for (int j1 = 0; j1 < W; ++j1) {

			if (city[i1][j1] != '#') {

				for (int k = 0; k < 4; ++k) {
					int i2 = i1 + rDir[k];
					int j2 = j1 + wDir[k];

					if (inRange(i2, j2) && city[i2][j2] != '#') {

						//���� ó�� -> ������ �б� ������ ���
						if ((id[i1][j1] == sId && id[i2][j2] == tId) || (id[i1][j1] == tId && id[i2][j2] == sId)) {
							cout << -1;
							return 0;
						}

						//(i1, j1)out ~ (i2, j2)in ���� �߰�
						addEdge(id[i1][j1] + 1, id[i2][j2], INF);
						//(i2, j2)out ~ (i1, j1)in ���� �߰�
						addEdge(id[i2][j2] + 1, id[i1][j1], INF);
					}
				}
			}
		}

	}

	//���� ��ǥ out -> �б� ��ǥ in ���
	cout << networkFlow(sId + 1, tId);

	return 0;
}