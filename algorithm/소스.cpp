#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	//루트 -1, 삭제 -2
	int parent[50];

	for (int i = 0; i < n; ++i) {
		int p;
		cin >> p;
		parent[i] = p;
	}

	//삭제될 노드의 번호
	int x;
	cin >> x;

	//루트가 삭제된 경우
	if (parent[x] == -1) {
		cout << 0;
		return 0;
	}

	//노드 삭제 & 이 노드를 부모로 하는 노드를 삭제하기 위해 큐에 저장
	queue<int> q;
	q.push(x);

	while (!q.empty()) {
		int p = q.front();
		//노드 삭제
		parent[p] = -2;
		q.pop();

		for (int i = 0; i < n; ++i) {
			//이 노드를 부모로 하는 노드 큐에 저장
			if (parent[i] == p) {
				q.push(i);
			}
		}
	}

	//리프 노드의 개수 확인
	int leaf = 0;
	for (int i = 0; i < n; ++i) {
		//삭제된 노드라면 건너뛴다
		if (parent[i] == -2) continue;

		bool isLeaf = true;
		for (int j = 0; j < n; ++j) {
			//자신을 부모로 갖는 노드가 있다면 리프 노드가 될 수 없다
			if (parent[j] == i) {
				isLeaf = false;
				break;
			}
		}

		if (isLeaf) leaf++;
	}

	cout << leaf;
	return 0;
}