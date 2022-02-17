#include <string>
#include <vector>
#include <cmath>
#include <deque>
#include <algorithm>

using namespace std;

typedef long long ll;

deque<string> calcList(deque<string> exp, string op) {

	deque <string> resultExp;

	while(!exp.empty()) {

		string top = exp.front();
		exp.pop_front();

		//원하는 연산자가 아닌 경우
		if (top != op) {
			resultExp.push_back(top);
			continue;
		}

		//원하는 연산자인 경우 
		ll num1 = stol(resultExp.back());
		resultExp.pop_back();
		ll num2 = stol(exp.front());
		exp.pop_front();

		//연산 결과
		ll num3;
		if (op == "*") num3 = num1 * num2;
		if (op == "+") num3 = num1 + num2;
		if (op == "-") num3 = num1 - num2;

		resultExp.push_back(to_string(num3));
	}

	return resultExp;
}

ll calcAnswer(deque <string> exp, char op1, char op2, char op3) {

	exp = calcList(exp, string(1, op1));
	exp = calcList(exp, string(1, op2));
	exp = calcList(exp, string(1, op3));
		
	if (exp.size() != 1) return 0;
	
	return abs(stol(exp.front()));
}

ll solution(string expression) {
	ll answer = 0;

	deque <string> exp;

	//주어진 수식 deque로 변환
	string num = "";
	for (int i = 0; i < expression.length(); ++i) {
		char ch = expression[i];

		if (ch == '+' || ch == '-' || ch == '*') {
			if (num != "") {
				exp.push_back(num);
				num = "";
			}

			exp.push_back(string(1, ch));
		}
		else num += ch;
	}
	if (num != "") exp.push_back(num);

	//각 우선순위에 따른 결괏값의 최댓값 구하기
	// + > - > *
	answer = max(answer, calcAnswer(exp, '+', '-', '*'));
	answer = max(answer, calcAnswer(exp, '+', '*', '-'));
	answer = max(answer, calcAnswer(exp, '-', '+', '*'));
	answer = max(answer, calcAnswer(exp, '-', '*', '+'));
	answer = max(answer, calcAnswer(exp, '*', '-', '+'));
	answer = max(answer, calcAnswer(exp, '*', '+', '-'));

	return answer;
}

