#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int solution(vector<string> words) {
	int answer = 0;
	for (int i = 0; i < words.size(); ++i) {
		string search = "";
		for (int j = 0; j < words[i].length(); ++j) {
			search += words[i][j];
			answer++;

			//search ���ڿ��� �˻����� �� �˻� ����� �ϳ��� ��ȯ�Ǵ��� �˻�
			bool flag = true;
			int cnt = 0;
			for (int k = 0; k < words.size(); ++k) {
				if (words[k].substr(0, search.length()) == search) cnt++;
				if (cnt > 1) {
					flag = false;
					break;
				}
			}

			if (flag) break;
		}
	}
	
	return answer;
}

int main() {
	solution({ "go", "gone", "guild" });
}