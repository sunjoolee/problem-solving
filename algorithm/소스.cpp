#include <algorithm>
#include <stack>
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//연산자의 rank 클수록 계산 우선순위 높음
	map<char, int> rank; 
	rank['('] = 0;
	rank['+'] = 1; rank['-'] = 1; 
	rank['*'] = 2; rank['/'] = 2;


	string inorder;
	//연산자 스택
	stack <char> st;

	cin >> inorder;
	for (int i = 0; i < inorder.length(); ++i) {
		char ch = inorder[i];
		//피연산자
		if (ch >= 'A' && ch <= 'Z') cout << ch;
		//여는 괄호
		else if (ch == '(') st.push('(');
		//닫는 괄호
		else if (ch == ')') {
			//여는 괄호까지 연산자 pop
			while (true) {
				if (st.top() == '(') {
					st.pop();
					break;
				}
				cout << st.top();
				st.pop();
			}
		}
		//연산자
		else{
			//st에 자신보다 높거나 같은 우선순위의 연산자가 들어있지 않도록 함
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