#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll;

list<string> calcList(list <string> exp, string op) {
	for (auto it = exp.begin(); it != exp.end(); ++it) {
		if (*it == op) {
			auto prevIt = --it;
			++it;
			auto nextIt = ++it;
			--it;

			ll num1 = stoi(*prevIt);
			ll num2 = stoi(*nextIt);
			
			exp.erase(prevIt);
			exp.erase(nextIt);

			//연산 결과
			ll num3;
			if (op == "*") num3 = num1 * num2;
			if (op == "+") num3 = num1 + num2;
			if (op == "-") num3 = num1 - num2;

			//연산자 위치 앞에 연산 결과 삽입
			exp.insert(it, to_string(num3));
			
			//연산자 삭제
			it = exp.erase(it);
			--it;
		}
	}

	return exp;
}

ll calcAnswer(list <string> exp, char op1, char op2, char op3) {

	exp = calcList(exp, string(1, op1));
	exp = calcList(exp, string(1, op2));
	exp = calcList(exp, string(1, op3));
	
	if (exp.size() != 1) return 0;

	return abs(stol(exp.front()));
}

ll solution(string expression) {
	ll answer = 0;

	list <string> exp;

	//주어진 수식 list로 변환
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

int main() {

	string expression;
	cin >> expression;

	solution(expression);

	return 0;
}