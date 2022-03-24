#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

bool checkBalance(string s) {
	int cnt1 = 0;
	int cnt2 = 0;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == '(') cnt1++;
		else cnt2++;
	}
	return cnt1 == cnt2;
}

bool checkCorrect(string s) {
	//빈 문자열인경우 참
	if (s == "") return true;

	stack<char> buffer;
	for (int i = 0; i < s.length(); ++i) {
		if (buffer.empty()) {
			buffer.push(s[i]);
			continue;
		}
		if (buffer.top() == '(' && s[i] == ')') buffer.pop();
		else buffer.push(s[i]);
	}
	return buffer.empty();
}

string correctU(string s) {
	// u가 올바른 괄호 문자열인 경우
	if (checkCorrect(s)) return s;

	// u의 맨 앞 & 맨 뒤 제거, 괄호 방향 바꾸기 
	string correct = "";
	for (int i = 1; i + 1 < s.length(); ++i) {
		if (s[i] == '(') correct += ")";
		else correct += "(";
	}

	return correct;
}

string correctString(string s) {
	if (checkCorrect(s)) return s;

	string u = "";
	string v = "";
	for (int i = 0; i < s.length(); ++i) {
		u += s[i];
		if (checkBalance(u)) {
			if (i + 1 < s.length())
				v = s.substr(i + 1);
			break;
		}
	}
	if(checkCorrect(u)) return u + correctString(v);
	else {
		string res = "(";
		res += correctString(v);
		res += ")";

	}
}

string solution(string p) {
	string answer = correctString(p);
	return answer;
}