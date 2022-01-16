#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//���� ����Ʈ�� ����-ǮĿ�� �˰��� �����ϱ�
const int MAX_V = 500;

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

	//v���� u�� ���� ������ �ʱ�ȭ�Ѵ�
	//�� ������ �뷮�� 0�� ���� �����̴�
	vu->target = u;
	vu->capacity = 0;
	vu->flow = 0;
	vu->reverse = uv;

	adj[u].push_back(uv);
	adj[v].push_back(vu);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	return 0;
}