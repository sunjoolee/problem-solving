#include <string>
#include <algorithm>
#include <vector>

using namespace std;

bool cmp(string s1, string s2) {
	//대소문자 구별 x
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);	// 소문자 변환
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);	// 소문자 변환

	//head, num, tail 분리
	string h1 = "";
	string num1 = "";

	bool headOver = false;
	for (int i = 0; i < s1.length(); ++i) {
		char ch = s1[i];

		//num 입력 받기
		if (ch >= '0' && ch <= '9') {
			headOver = true;
			num1 += ch;
		}
		//head 입력받기
		else if (!headOver) {
			h1 += ch;
			continue;
		}
		//num과 head 입력 받기 끝난 경우 종료 (tail 필요 X)
		else break;
	}

	string h2 = "";
	string num2 = "";

	headOver = false;
	for (int i = 0; i < s2.length(); ++i) {
		char ch = s2[i];

		//num 입력 받기
		if (ch >= '0' && ch <= '9') {
			headOver = true;
			num2 += ch;
		}
		//head 입력받기
		else if (!headOver) {
			h2 += ch;
			continue;
		}
		//num과 head 입력 받기 끝난 경우 종료 (tail 필요 X)
		else break;
	}

	//head 사전순으로 정렬
	if (h1 < h2) return true;
	if (h1 == h2) {
		//head 동일한 경우 num 숫자 순으로 정렬
		//head, num 동일한 경우 입력 순으로 정렬됨 (stable_sort)
		return stoi(num1) < stoi(num2);
	}
	return false;
}

vector<string> solution(vector<string> files) {
	
	stable_sort(files.begin(), files.end(), cmp);
	
	vector<string> answer(files.begin(), files.end());
	return answer;
}