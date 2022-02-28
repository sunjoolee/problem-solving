#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

map <string, char> stringToChar;

int solution(string s) {

	stringToChar.insert({ "zero", '0' });
	stringToChar.insert({ "one", '1' });
	stringToChar.insert({ "two", '2' });
	stringToChar.insert({ "three", '3' });
	stringToChar.insert({ "four", '4' });
	stringToChar.insert({ "five", '5' });
	stringToChar.insert({ "six", '6' });
	stringToChar.insert({ "seven", '7' });
	stringToChar.insert({ "eight", '8' });
	stringToChar.insert({ "nine", '9' });

	int answer = 0;
	string answerString = "";
	
	string in;
	for (int i = 0; i < s.length(); ++i) {
		char ch = s[i];

		if (ch >= '0' && ch <= '9') {
			answerString += ch;
			continue;
		}

		in += ch;
		if (stringToChar.find("in") != stringToChar.end()) {
			answerString += stringToChar[in];
			in = "";
		}
	}

	answer = stoi(answerString);
	return answer;
}

int main() {
	string s;
	cin >> s;
	solution(s);
}