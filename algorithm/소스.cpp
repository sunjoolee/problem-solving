#include <iostream>
#include <string>
#include <deque>
using namespace std;

deque <char> leftDQ;
deque <char> rightDQ;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string input;
	cin >> input;

	for (int i = 0; input[i] != NULL; ++i) {
		leftDQ.push_back(input[i]);
	}

	int M;
	cin >> M;
	while (M--) {
		char instruction, x;
		cin >> instruction;
		
		//Ŀ�� ��������
		if (instruction == 'L') {
			if (leftDQ.empty()) continue;

			x = leftDQ.back();
			leftDQ.pop_back();
			rightDQ.push_front(x);
		}
		//Ŀ�� ����������
		else if (instruction == 'D') {
			if (rightDQ.empty()) continue;

			x = rightDQ.front();
			rightDQ.pop_front();
			leftDQ.push_back(x);
		}
		//Ŀ�� ���� ���� ����
		else if (instruction == 'B') {
			if (leftDQ.empty()) continue;
			leftDQ.pop_back();
		}
		//Ŀ�� ���� ���� �߰�
		else if (instruction == 'P') {
			cin >> x;
			leftDQ.push_back(x);
		}
	}

	for (auto it = leftDQ.begin(); it != leftDQ.end(); ++it)
		cout << *it;
	for (auto it = rightDQ.begin(); it != rightDQ.end(); ++it)
		cout << *it;

	return 0;
}