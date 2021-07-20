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

	int T;
	cin >> T;
	while (T--) {

		string input;
		cin >> input;

		for (int i = 0; input[i] != NULL; ++i) {
			char x = input[i];

			//Ŀ�� ��������
			if (x == '<') {
				if (leftDQ.empty()) continue;

				char tmp = leftDQ.back();
				leftDQ.pop_back();
				rightDQ.push_front(tmp);
			}
			//Ŀ�� ����������
			else if (x == '>') {
				if (rightDQ.empty()) continue;

				char tmp = rightDQ.front();
				rightDQ.pop_front();
				leftDQ.push_back(tmp);
			}
			//Ŀ�� ���� ���� ����
			else if (x == '-') {
				if (leftDQ.empty()) continue;
				leftDQ.pop_back();
			}
			//Ŀ�� ���� ���� �߰�
			else {
				leftDQ.push_back(x);
			}
		}

		for (auto it = leftDQ.begin(); it != leftDQ.end(); ++it)
			cout << *it;
		for (auto it = rightDQ.begin(); it != rightDQ.end(); ++it)
			cout << *it;
		cout << endl;

		leftDQ.clear();
		rightDQ.clear();
	}

	return 0;
}