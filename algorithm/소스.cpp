#include <string>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

string solution(int n, int k, vector<string> cmd) {
	string answer = "";

	vector<char> table(n, 'O');
	stack <int> deleted;

	for (int i = 0; i < cmd.size(); ++i) {
		string curCmd = cmd[i];

		if (curCmd[0] == 'D') {
			//move��ŭ �Ʒ��� �̵�
			int move = stoi(curCmd.substr(2));
			while (move != 0) {
				if (table[k + 1] == 'O') {
					k++;
					move--;
				}
				else k++;
			}
		}
		else if (curCmd[0] == 'U') {
			//move��ŭ ���� �̵�
			int move = stoi(curCmd.substr(2));
			while (move != 0) {
				if (table[k - 1] == 'O') {
					k--;
					move--;
				}
				else k--;
			}
		}
		else if (curCmd[0] == 'C') {
			//���õ� �� ����
			table[k] ='X';
			deleted.push(k);
			
			int tmp = k;
			bool move = false;

			//�� ĭ �Ʒ��� �̵�
			while(!move) {
				if (tmp + 1 == n) break;

				if (table[tmp + 1] == 'O') {
					k = tmp + 1;
					move = true;
				}
				else tmp++;
			}

			//�Ʒ� ĭ�� ���� ��� �� ĭ ���� �̵�
			tmp = k;
			while(!move) {
				if (table[tmp - 1] == 'O') {
					k = tmp - 1;
					move = true;
				}
				else tmp--;
			}
		}
		else if (curCmd[0] == 'Z') {
			//���� �ֱٿ� ������ �� ����
			table[deleted.top()] = 'O';
			deleted.pop();
		}
	}

	for (int i = 0; i < n; ++i) {
		answer += table[i];
	}
	return answer;
}

int main() {
	int n, k;
	vector<string> cmd;

	n = 8;
	k = 2;
	cmd.push_back("D 2");
	cmd.push_back("C");
	cmd.push_back("U 3");
	cmd.push_back("C");
	cmd.push_back("D 4");
	cmd.push_back("C");
	cmd.push_back("U 2");
	cmd.push_back("Z");
	cmd.push_back("Z");

	solution(n, k, cmd);
}