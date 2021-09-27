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
//sccComponent[sccId]: sccId를 갖는 컴포넌트에 포함된 정점의 집합
vector<vector<int>> sccComponent;

//정점의 번호를 담는 스택
stack<int> st;


//here를 루트로 하는 서브트리에서 역방향 간선이나 교차 간선을 통해 갈 수 있는 정점 중 최소 발견 순서 반환
//이미 SCC로 묶인 정점으로 연결된 간선은 무시한다
int scc(int here) {
	int ret = discovered[here] = vertexCounter++;

	//스택에 here을 넣는다
	//here의 자손들은 모두 스택에서 here 위에 쌓이게 된다
	st.push(here);

	for (int i = 0; i < adj[here].size(); ++i) {
		int there = adj[here][i];

		//(here, there)이 트리 간선인 경우
		if (discovered[there] == -1) {
			ret = min(ret, scc(there));
		}
		//(here, there)이 무시해야하는 교차 간선이 아닌 경우
		else if (sccId[there] == -1) {
			ret = min(ret, discovered[there]);
		}
	}

	//here에서 부모로 올라가는 간선을 끊어도 되는 경우 
	//= here를 루트로 하는 서브트리에서 갈 수 있는 정점 중 가장 높은 정점이 here인 경우
	if (ret == discovered[here]) {
		//here을 루트로 하는 서브트리에 남아 있는 정점들을 하나의 컴포넌트로 묶는다
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

	//초기화
	adj = vector<vector<int>> (V, vector<int>(0));
	discovered = vector<int>(adj.size(), -1);
	sccId = vector<int>(V, -1);

	//그래프 입력 받기
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

	//결과 출력
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