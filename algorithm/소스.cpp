#include <algorithm>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

//�������� ����
bool cmp(int a, int b) {
	return a > b;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		int n;
		int m;
		cin >> n >> m;
		
		//<doc, priority>
		queue<pair<int, int>> q;
		vector<int> maxPriority;
		for (int i = 0; i < n; ++i) {
			int priority;
			cin >> priority;
			q.push({ i, priority });
			maxPriority.push_back(priority);
		}
		sort(maxPriority.begin(), maxPriority.end(), cmp);

		//������ ��µǴ� ����
		int seq = 0;
		//maxPriority index
		int idx = 0;
		while (true) {
			int curDoc = q.front().first; 
			int curPriority = q.front().second;

			if (curPriority == maxPriority[idx]) {
				//���
				seq++;
				q.pop();
				idx++;
				if (curDoc == m) break;
			}
			else {
				//ť �� �ڷ� �̵�
				q.push(q.front());
				q.pop();
			}
		}
		cout << seq << "\n";
	}
	return 0;
}