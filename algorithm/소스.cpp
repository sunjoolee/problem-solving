#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <map>
#include <algorithm>
using namespace std;

//��Ʈ��ũ ���� ������ �ذ��ϴ� ����-��Ŀ�� �˰����� ����

//������ �ִ� ���� = �ҹ��� + �빮��
const int MAX_V = 55;
const int INF = 987654321;
int V;

//capacity[u][v] = u���� v�� ���� �� �ִ� �뷮
//flow[u][v] = u���� v�� �귯���� ���� (�ݴ� ������ ��� ����)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

//flow[]�� ����ϰ� �� ������ ��ȯ�Ѵ�.
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//�������� ����
	int N;
	cin >> N;
	
	//�������� ����� ���ĺ��� ��ȣ ����
	V = 0;
	map<char, int> id;

	//capacity�� 0���� �ʱ�ȭ�Ѵ�.
	memset(capacity, 0, sizeof(capacity));

	for (int i = 0; i < N; ++i) {
		char node1, node2; int capa;
		cin >> node1 >> node2 >> capa;

		if (id.find(node1) == id.end())
			id[node1] = V++;
		
		if (id.find(node2) == id.end())
			id[node2] = V++;
		
		//����� ������
		capacity[id[node1]][id[node2]] = capa;
		capacity[id[node2]][id[node1]] = capa;
	}

	//A���� Z���� �ִ� ���� ���
	cout << networkFlow(id['A'], id['Z']);
	return 0;
}