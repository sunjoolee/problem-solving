#include <string>
#include <algorithm>
#include <vector>

using namespace std;

bool cmp(string s1, string s2) {
	//��ҹ��� ���� x
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);	// �ҹ��� ��ȯ
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);	// �ҹ��� ��ȯ

	//head, num, tail �и�
	string h1 = "";
	string num1 = "";

	bool headOver = false;
	for (int i = 0; i < s1.length(); ++i) {
		char ch = s1[i];

		//num �Է� �ޱ�
		if (ch >= '0' && ch <= '9') {
			headOver = true;
			num1 += ch;
		}
		//head �Է¹ޱ�
		else if (!headOver) {
			h1 += ch;
			continue;
		}
		//num�� head �Է� �ޱ� ���� ��� ���� (tail �ʿ� X)
		else break;
	}

	string h2 = "";
	string num2 = "";

	headOver = false;
	for (int i = 0; i < s2.length(); ++i) {
		char ch = s2[i];

		//num �Է� �ޱ�
		if (ch >= '0' && ch <= '9') {
			headOver = true;
			num2 += ch;
		}
		//head �Է¹ޱ�
		else if (!headOver) {
			h2 += ch;
			continue;
		}
		//num�� head �Է� �ޱ� ���� ��� ���� (tail �ʿ� X)
		else break;
	}

	//head ���������� ����
	if (h1 < h2) return true;
	if (h1 == h2) {
		//head ������ ��� num ���� ������ ����
		//head, num ������ ��� �Է� ������ ���ĵ� (stable_sort)
		return stoi(num1) < stoi(num2);
	}
	return false;
}

vector<string> solution(vector<string> files) {
	
	stable_sort(files.begin(), files.end(), cmp);
	
	vector<string> answer(files.begin(), files.end());
	return answer;
}