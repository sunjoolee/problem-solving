#include <algorithm>
#include <string>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	string str;
	cin >> str;

	vector<double> alpha;
	for (int i = 0; i < n; ++i) {
		double input;
		cin >> input;
		alpha.push_back(input);
	}

	stack<double> st;
	for (int i = 0; i < str.length(); ++i) {
		char ch = str[i];
		//�������� ���
		if (ch == '+') {
			double db2 = st.top();
			st.pop();
			double db1 = st.top();
			st.pop();

			st.push(db1 + db2);

		}
		else if (ch == '-') {
			double db2 = st.top();
			st.pop();
			double db1 = st.top();
			st.pop();

			st.push(db1 - db2);
		}
		else if (ch == '*') {
			double db2 = st.top();
			st.pop();
			double db1 = st.top();
			st.pop();

			st.push(db1 * db2);
		}
		else if (ch == '/') {
			double db2 = st.top();
			st.pop();
			double db1 = st.top();
			st.pop();
			st.push(db1 / db2);
		}
		//�ǿ������� ���
		else {
			//���ĺ� -> �����ϴ� ���ڷ� ġȯ�Ͽ� ���ÿ� ����
			st.push(alpha[ch - 'A']);
		}
	}

	//�Ҽ��� �Ʒ� 2�ڸ����� ���
	cout << fixed;
	cout.precision(2);
	cout << st.top();

	return 0;
}