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

		//종료 조건
		if (input == ".") break;

		stack<char> st;
		bool balance = true;
		
		//문자열 검사
		for (int i = 0; i < input.size(); ++i) {
			char curchar = input[i];
			
			//여는 괄호인 경우 push
			if (curchar == '(' || curchar == '[')
				st.push(curchar);

			//닫는 괄호인 경우 짝 맞으면 pop
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
		//문자열 검사 종료 후 스택 비어있지 않은 경우
		//문자열 균형을 이루지 않는다
		if (!st.empty()) 
			balance = false;

		if (balance) cout << "yes\n";
		else cout << "no\n";

	}
	return 0;
}