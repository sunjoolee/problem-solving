#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory.h>
#include <map>
#include <algorithm>
using namespace std;

//���� ����Ʈ�� ����-ǮĿ�� �˰��� �����ϱ�

const int INF = 987654321;
const int MAX_V = 60;

//������ ����
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

	//v���� u�� ���� ������ �ʱ�ȭ�Ѵ� (����� ����)
	vu->target = u;
	vu->capacity = capacity;
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//�������� ����
	int N;
	cin >> N;

	//�������� ����� ���ĺ��� ��ȣ ����
	V = 0;
	map<char, int> id;

	//�������� ������ ���� ����
	int makeEdge[MAX_V][MAX_V];
	memset(makeEdge, 0, sizeof(makeEdge));

	for (int i = 0; i < N; ++i) {
		char node1, node2; 
		int capa;
		cin >> node1 >> node2 >> capa;

		if (id.find(node1) == id.end()) {
			id[node1] = V++;
		}
		if (id.find(node2) == id.end()) {
			id[node2] = V++;
		}

		if(id[node1] <= id[node2]) makeEdge[id[node1]][id[node2]] += capa;
		else makeEdge[id[node2]][id[node1]] += capa;
	}


	//���� �����
	for (int i = 0; i < V; ++i) {
		for (int j = i; j < V; ++j) {
			//����� ������
			addEdge(i, j, makeEdge[i][j]);
		}
	}

	//A���� Z���� �ִ� ���� ���
	cout << networkFlow(id['A'], id['Z']);

	return 0;
}