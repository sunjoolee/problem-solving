#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

const int MAXN = 1001;

//�ǹ��� ���µ� �ɸ��� �ð�
ll delay[MAXN] = { 0 };

//�ǹ��� ���� �����ϴ� ����
ll construct[MAXN] = { 0 };

//inDegree[i]: ����i�� ���� ������ ��
int inDegree[MAXN] = { 0 };

//vector<int> child[i]: ���i�� ���� ���� �ϴ� ������ ����
vector<int> child[MAXN];


//���� ���� �Լ�
int topologySort(int n, int w) {
	
	queue<int> q;

	//���� ���� 0�� ���� ť�� ����
	for (int i = 1; i <= n; ++i) {
		if (inDegree[i] == 0) q.push(i);
	}

	//������ ������ ����Ǳ���� n���� ������ �湮�Ѵ�
	for (int i = 1; i <= n; ++i) {

		//n���� ������ �湮�ϱ� ���� ť�� �������� ����Ŭ�� �߻��� ��
		if (q.empty()) return -1;
		

		//���� ������ 0�� ���� ����
		int parent = q.front();

		//�¸��ϱ� ���� �Ǽ��ؾ��ϴ� �ǹ��� ���
		if (parent == w) return construct[w] + delay[w];

		//���õ� ������ ���⿡ �μӵ� ��� ������ ����
		q.pop();
		for (int i = 0; i < child[parent].size(); ++i) {
			int childnode = child[parent][i];
			inDegree[childnode]--;

			//child �ǹ��� ���� �����ϴ� ����
			construct[childnode] = max(construct[childnode], construct[parent] + delay[parent]);

			//���Ӱ� ���������� 0�� �� ������ ť�� ����
			if (inDegree[childnode] == 0) {
				q.push(childnode);
			}
		}
	}
	return -1;
}


int main() {
	
	//�׽�Ʈ ���̽� ��
	int t;
	cin >> t;
	while(t--){
		//�ʱ�ȭ
		for (int i = 0; i < MAXN; ++i) {
			delay[i] = 0;
			construct[i] = 0;
			inDegree[i] = { 0 };
			child[i].clear();

		}
		//�ǹ� ��
		int n;
		cin >> n;
		//�ǹ� ��Ģ ��
		int k;
		cin >> k;

		for (int i = 1; i <= n; ++i) {
			ll d;
			cin >> d;
			delay[i] = d;
		}

		for (int i = 0; i < k; ++i) {
			int x, y;
			cin >> x >> y;
			child[x].push_back(y);
			inDegree[y]++;
		}

		//�¸��ϱ� ���� �Ǽ��ؾ��ϴ� �ǹ� ��ȣ
		int w;
		cin >> w;

		cout << topologySort(n,w) <<"\n";
	}
	return 0;
}