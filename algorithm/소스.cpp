#include <algorithm>
#include <stack>
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//�������� rank Ŭ���� ��� �켱���� ����
	map<char, int> rank; 
	rank['('] = 0;
	rank['+'] = 1; rank['-'] = 1; 
	rank['*'] = 2; rank['/'] = 2;


	string inorder;
	//������ ����
	stack <char> st;

	cin >> inorder;
	for (int i = 0; i < inorder.length(); ++i) {
		char ch = inorder[i];
		//�ǿ�����
		if (ch >= 'A' && ch <= 'Z') cout << ch;
		//���� ��ȣ
		else if (ch == '(') st.push('(');
		//�ݴ� ��ȣ
		else if (ch == ')') {
			//���� ��ȣ���� ������ pop
			while (true) {
				if (st.top() == '(') {
					st.pop();
					break;
				}
				cout << st.top();
				st.pop();
			}
		}
		//������
		else{
			//st�� �ڽź��� ���ų� ���� �켱������ �����ڰ� ������� �ʵ��� ��
			while (!st.empty()) {
				if (rank[st.top()] < rank[ch]) break;
				cout << st.top();
				st.pop();
			}
			st.push(ch);
		}
	}
	while (!st.empty()) {
		cout << st.top();
		st.pop();
	}

	return 0;
}