#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 987654321;

vector<int> bfs(int n) {

	queue<pair<int, vector<int>>> q;
	vector<int> visited(n + 1, INF);

	q.push({ n, vector<int>(1, n)});

	while (!q.empty()) {
		int num = q.front().first;
		vector<int> v = q.front().second;
		q.pop();

		if (visited[num] < v.size() - 1) continue;
		visited[num] = v.size() - 1;

		if (num == 1) {
			return v;
		}

		//X가 3으로 나누어 떨어지면, 3으로 나눈다.
		if (num % 3 == 0) {
			v.push_back(num / 3);
			q.push({ num / 3, v });
			v.pop_back();
		}
		//X가 2로 나누어 떨어지면, 2로 나눈다.
		if (num % 2 == 0) {
			v.push_back(num / 2);
			q.push({ num / 2, v });
			v.pop_back();
		}
		//1을 뺀다.
		v.push_back(num - 1);
		q.push({ num - 1, v });
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;
	vector<int> answer = bfs(n);

	cout << answer.size() - 1<<"\n";
	for (int i = 0; i < answer.size(); ++i)
		cout << answer[i] << " ";

	return 0;
}