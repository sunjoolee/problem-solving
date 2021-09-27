#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int V, E;
vector<vector<int>> adj;

int vertexCounter = 0;
vector<int> discovered;

int sccCounter = 0;
vector<int> sccId;
//sccComponent[sccId]: sccId�� ���� ������Ʈ�� ���Ե� ������ ����
vector<vector<int>> sccComponent;

//������ ��ȣ�� ��� ����
stack<int> st;


//here�� ��Ʈ�� �ϴ� ����Ʈ������ ������ �����̳� ���� ������ ���� �� �� �ִ� ���� �� �ּ� �߰� ���� ��ȯ
//�̹� SCC�� ���� �������� ����� ������ �����Ѵ�
int scc(int here) {
	int ret = discovered[here] = vertexCounter++;

	//���ÿ� here�� �ִ´�
	//here�� �ڼյ��� ��� ���ÿ��� here ���� ���̰� �ȴ�
	st.push(here);

	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];

		//(here, there)�� Ʈ�� ������ ���
		if (discovered[there] == -1) {
			ret = min(ret, scc(there));
		}
		//(here, there)�� �����ؾ��ϴ� ���� ������ �ƴ� ���
		else if (sccId[there] == -1) {
			ret = min(ret, discovered[there]);
		}
	}

	//here���� �θ�� �ö󰡴� ������ ��� �Ǵ� ��� 
	//= here�� ��Ʈ�� �ϴ� ����Ʈ������ �� �� �ִ� ���� �� ���� ���� ������ here�� ���
	if (ret == discovered[here]) {
		//here�� ��Ʈ�� �ϴ� ����Ʈ���� ���� �ִ� �������� �ϳ��� ������Ʈ�� ���´�
		vector<int> component;
		while (true) {
			int t = st.top();
			st.pop();
			
			sccId[t] = sccCounter;
			component.push_back(t);

			if (t == here) break;
		}

		sort(component.begin(), component.end());
		sccComponent.push_back(component);

		sccCounter++;
	}
	return ret;
}

bool cmp(const vector<int>& a, const vector<int>& b) {
	return a[0] < b[0];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> V >> E;

	//�ʱ�ȭ
	adj = vector<vector<int>> (V, vector<int>(0));
	discovered = vector<int>(adj.size(), -1);
	sccId = vector<int>(V, -1);

	//�׷��� �Է� �ޱ�
	for (int i = 0; i < E; ++i) {
		int A, B;
		cin >> A >> B;
		
		adj[A - 1].push_back(B - 1);
	}

	//scc all
	for (int i = 0; i < V; ++i) {
		if (discovered[i] == -1)
			scc(i);
	}

	//��� ���
	cout << sccCounter << "\n";
	
	sort(sccComponent.begin(), sccComponent.end(), cmp);

	for (int i = 0; i < sccComponent.size(); ++i) {
		for (int j = 0; j < sccComponent[i].size(); ++j) {
			cout << sccComponent[i][j] + 1 << " ";
		}
		cout << "-1\n";
	}

	return 0;
}