#include <string>
#include <math.h>
#include <deque>

using namespace std;


int solution(string dartResult) {
	
	deque <int> score;

	string num = "";
	for (int i = 0; i < dartResult.length(); ++i) {
		char ch = dartResult[i];
		//������ ���
		if (ch >= '0' && ch <= '9') num += ch;
		//���ʽ��� ���
		else if (ch == 'S') {
			score.push_back(stoi(num));
			num = "";
		}
		else if (ch == 'D') {
			score.push_back(stoi(num) * stoi(num));
			num = "";
		}
		else if (ch == 'T') {
			score.push_back(stoi(num) * stoi(num) * stoi(num));
			num = "";
		}
		//�ɼ��� ���
		else if (ch == '*') {
			int sc1 = score.back();
			score.pop_back();
			int sc2 = score.back();
			score.pop_back();

			score.push_back(sc2 * 2);
			score.push_back(sc1 * 2);
		}
		else if (ch == '#') {
			int sc = score.back();
			score.pop_back();
			
			score.push_back(-sc);
		}
	}

	int answer = 0;
	


	return answer;
}