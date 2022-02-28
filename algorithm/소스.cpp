#include <string>
#include <map>
#include <algorithm>
using namespace std;

int solution(string str1, string str2) {

	//��ҹ��� ���� X -> ��� �ҹ��ڷ� ��ȯ
	transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
	transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

	map<string, int> m1;
	map<string, int> m2;

	for (int i = 0; i < str1.size() - 1; ++i) {
		if (str1[i] < 'a' || str1[i] > 'z') continue;
		if (str1[i+1] < 'a' || str1[i+1] > 'z') continue;

		string back = str1.substr(i, 2);
		if (m1.find(back) == m1.end()) {
			m1[back] = 1;
		}
		else m1[back]++;
	}
	for (int i = 0; i < str2.size() - 1; ++i) {
		if (str2[i] < 'a' || str2[i] > 'z') continue;
		if (str2[i + 1] < 'a' || str2[i + 1] > 'z') continue;

		string back = str2.substr(i, 2);
		if (m2.find(back) == m2.end()) {
			m2[back] = 1;
		}
		else m2[back]++;
	}

	//�������� ũ��, �������� ũ�� ���ϱ�
	int gyo = 0;
	int hap = 0;

	for (auto it = m1.begin(); it != m1.end(); ++it) {
		string str = it->first;
		int val = it->second;

		if (m2.find(str) == m2.end()) {
			hap += val;
		}
		else {
			gyo += min(m2[str], val);
			hap += max(m2[str], val);
			m2.erase(str);
		}
	}
	//m1�� �ߺ����� ���� str�� ���� ����
	for (auto it = m2.begin(); it != m2.end(); ++it) {
		hap += it ->second;
	}

	int answer = 0;
	answer = 65536 * gyo / hap;
	return answer;
}

int main() {
	solution("E=M*C^2", "e=m*c^2");
}