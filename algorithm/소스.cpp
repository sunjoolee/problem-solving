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

			//커서 왼쪽으로
			if (x == '<') {
				if (leftDQ.empty()) continue;

				char tmp = leftDQ.back();
				leftDQ.pop_back();
				rightDQ.push_front(tmp);
			}
			//커서 오른쪽으로
			else if (x == '>') {
				if (rightDQ.empty()) continue;

				char tmp = rightDQ.front();
				rightDQ.pop_front();
				leftDQ.push_back(tmp);
			}
			//커서 왼쪽 문자 삭제
			else if (x == '-') {
				if (leftDQ.empty()) continue;
				leftDQ.pop_back();
			}
			//커서 왼쪽 문자 추가
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