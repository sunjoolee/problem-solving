#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n;
priority_queue<int> maxheap;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;

		//����
		if (input > 0)
			maxheap.push(input);

		//�ִ� ���� ��� & ����
		else {
			if (maxheap.empty())
				cout << 0 <<"\n";
			else {
				cout << maxheap.top() << "\n";
				maxheap.pop();
			}
		}
	}
	return 0;
}