#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true) {
		string input;
		getline(cin, input);

		//���� ����
		if (input == ".") break;

		stack<char> st;
		bool balance = true;
		
		//���ڿ� �˻�
		for (int i = 0; i < input.size(); ++i) {
			char curchar = input[i];
			
			//���� ��ȣ�� ��� push
			if (curchar == '(' || curchar == '[')
				st.push(curchar);

			//�ݴ� ��ȣ�� ��� ¦ ������ pop
			else if (curchar == ')') {
				if (!st.empty() && st.top() == '(') st.pop();
				else {
					balance = false;
					break;
				}
			}
			else if (curchar == ']') {
				if (!st.empty() && st.top() == '[') st.pop();
				else {
					balance = false;
					break;
				}
			}
		}
		//���ڿ� �˻� ���� �� ���� ������� ���� ���
		//���ڿ� ������ �̷��� �ʴ´�
		if (!st.empty()) 
			balance = false;

		if (balance) cout << "yes\n";
		else cout << "no\n";

	}
	return 0;
}