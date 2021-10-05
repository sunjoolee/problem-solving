#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, k;

int bfs(int start) {
	//<��ġ,�ð�>
	queue<pair<int, int>> q;
	int found[200001] = { 0 };

	found[start] = 1;
	q.push({ start, 0 });

	while (!q.empty()) {
		int here = q.front().first;
		int time = q.front().second;
		q.pop();

		//���� ��ġ �湮�ϱ�
		if (here == k) return time;

		//�ڷ� �ȱ�
		if (here - 1 > 0 && found[here - 1] == 0) {
			found[here - 1] =  1;
			q.push({ here - 1, time + 1});
		}
		//������ �ȱ�
		if (here + 1 < 200001 && found[here + 1] == 0) {
			found[here + 1] = 1;
			q.push({ here + 1, time + 1 });
		}
		//�����̵� �ϱ�
		if (here * 2 < 200001 && found[here * 2] == 0) {
			found[here * 2] = 1;
			q.push({ here * 2, time + 1 });
		}
	}

	//oops
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> k;

	if (n == k) {
		cout << 0;
		return 0;
	}

	cout << bfs(n);
	return 0;
}