#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 100005;

//해당 숫자가 집합에 몇 번 포함되었는지 저장
int arr[MAX_SIZE] = { 0 };

bool cmp(int i, int j) {
	return j < i;
}

vector<int> solution(string s) {
	//가장 최대 중복 횟수 = 튜플의 길이
	int numMax = 0;

	string num = "";
	for (int i = 0; i < s.length(); ++i) {
		char ch = s[i];

		if (ch == '{' || ch == '"') continue;
		else if (ch == ',' || ch == '}') {
			if (num == "") continue;
			
			int pos = stoi(num);
			arr[pos]++;
			if (numMax < arr[pos]) numMax = arr[pos];
			num = "";
		}
		else num += ch;
	}

	vector<int> answer(numMax, 0);
	for (int i = 0; i < MAX_SIZE; ++i) {
		if (arr[i] == 0) continue;
		answer[arr[i] - 1] = i;
	}
	reverse(answer.begin(), answer.end());

	return answer;
}

int main() {
	string input;
	cin >> input;

	solution(input);

}

