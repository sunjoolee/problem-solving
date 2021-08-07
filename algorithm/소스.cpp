#include <iostream>
#include <cstring>
#include<vector>
#include <set>
using namespace std;

int input[200001];
int parent[200001];

set <int> node;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> input[i];

	memset(parent, -1, sizeof(parent));

	
	for (int i = 0; i < n; ++i) {
		int curnode = input[i];
		node.insert(curnode);

		//아직 parent를 모르는 노드의 경우
		//parent는 경로에서 자신 바로 앞에 있는 노드
		if (parent[curnode] == -1) {
			parent[curnode] = input[i - 1];
		}
	}
	//루트 노드는 부모 도시 -1
	parent[input[0]] = -1;

	//도시의 개수
	cout << node.size() << "\n";
	for (auto it = node.begin(); it != node.end(); ++it)
		cout << parent[*it] << " ";

	return 0;
}