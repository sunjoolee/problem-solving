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

			//���� ���
			ll num3;
			if (op == "*") num3 = num1 * num2;
			if (op == "+") num3 = num1 + num2;
			if (op == "-") num3 = num1 - num2;

			//������ ��ġ �տ� ���� ��� ����
			exp.insert(it, to_string(num3));
			
			//������ ����
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

	//�־��� ���� list�� ��ȯ
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

	//�� �켱������ ���� �ᱣ���� �ִ� ���ϱ�
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