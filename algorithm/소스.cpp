#include <algorithm>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

//내림차순 정렬
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

		//문서가 출력되는 순서
		int seq = 0;
		//maxPriority index
		int idx = 0;
		while (true) {
			int curDoc = q.front().first; 
			int curPriority = q.front().second;

			if (curPriority == maxPriority[idx]) {
				//출력
				seq++;
				q.pop();
				idx++;
				if (curDoc == m) break;
			}
			else {
				//큐 맨 뒤로 이동
				q.push(q.front());
				q.pop();
			}
		}
		cout << seq << "\n";
	}
	return 0;
}