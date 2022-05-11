#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;


vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;

	map<string, vector<int>> m;

	//"java backend junior pizza 150"
	for (int i = 0; i < info.size(); ++i) {
		vector<string> jogun;
		int score;

		string buffer = "";
		for (int j = 0; j < info[i].length(); ++j) {
			if (info[i][j] == ' ') {
				jogun.push_back(buffer);
				buffer = "";
			}
			else buffer += info[i][j];
		}
		score = stoi(buffer);

		//m�� ���� 
		//������ ù ���ڸ� �̿��Ͽ� m �˻� key �����
		vector<string> keys;
		string key = "----";
			key[0] = jogun[0][0];
				key[1] = jogun[1][0];
					key[2] = jogun[2][0];
						key[3] = jogun[3][0];
						keys.push_back(key); //0123
						key[3] = '-';
						keys.push_back(key); //012-
					key[2] = '-';
						key[3] = jogun[3][0];
						keys.push_back(key); //01-3
						key[3] = '-';
						keys.push_back(key); //01--
				key[1] = '-';
					key[2] = jogun[2][0];
						key[3] = jogun[3][0];
						keys.push_back(key); //0-12
						key[3] = '-';
						keys.push_back(key); //0-1-
					key[2] = '-';
						key[3] = jogun[3][0];
						keys.push_back(key); //0--3
						key[3] = '-';
						keys.push_back(key); //0---
			key[0] = '-';
				key[1] = jogun[1][0];
					key[2] = jogun[2][0];
						key[3] = jogun[3][0];
						keys.push_back(key); //-123
						key[3] = '-';
						keys.push_back(key); //-12-
					key[2] = '-';
						key[3] = jogun[3][0];
						keys.push_back(key); //-1-3
						key[3] = '-';
						keys.push_back(key); //-1--
				key[1] = '-';
					key[2] = jogun[2][0];
						key[3] = jogun[3][0];
						keys.push_back(key); //--23
						key[3] = '-';
						keys.push_back(key); //--2-
					key[2] = '-';
						key[3] = jogun[3][0];
						keys.push_back(key); //---3
						key[3] = '-';
						keys.push_back(key); //----

		for (int i = 0; i < keys.size(); ++i) {
			if (m.find(keys[i]) == m.end())
				m[keys[i]] = vector<int>(1, score);
			else
				m[keys[i]].push_back(score);
		}
	}


	//�������� ����
	//query�� ó���ϴ� �ݺ��� �ٱ����� �����ؾ� �ð��ʰ��� ���� �ʴ´�!!
	for (auto it = m.begin(); it != m.end(); ++it) {
		sort(it->second.begin(), it->second.end());
	}
	
	//"cpp and - and senior and pizza 250"
	for (int i = 0; i < query.size(); ++i) {
		string jogun = "";
		int score;

		string buffer = "";
		for (int j = 0; j < query[i].length(); ++j) {
			if (query[i][j] == ' ') {
				//m �˻��� ���� ������ ù ���ڸ� ����
				if(buffer != "and") jogun = jogun + buffer[0];
				buffer = "";
			}
			else buffer += query[i][j];
		}
		score = stoi(buffer);

		//query ���ǿ� �´� �ĺ����� ����
		vector<int> hoobo = m[jogun];

		//lower_bound = ã������ key ������ ���ų� ū ���ڰ� �迭 �� ��°���� ó�� �����ϴ��� 
		answer.push_back(hoobo.size() - (lower_bound(hoobo.begin(), hoobo.end(), score) - hoobo.begin()));
	}

	return answer;
}

int main() {
	solution({ "java backend junior pizza 150", "python frontend senior chicken 210", "python frontend senior chicken 150", "cpp backend senior pizza 260", "java backend junior chicken 80", "python backend senior chicken 50" }, { "java and backend and junior and pizza 100", "python and frontend and senior and chicken 200", "cpp and - and senior and pizza 250", "- and backend and senior and - 150", "- and - and - and chicken 100", "- and - and - and - 150" });
}