#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

map<string, vector<int>> m;

void insertInMap(string key, int idx, vector<string> jogun, int score) {
	if (idx == jogun.size()) {
		if (m.find(key) == m.end()) 
			m[key] = vector<int>(1, score);
		else 
			m[key].push_back(score);
		
		return;
	}

	insertInMap(key + jogun[idx], idx+1, jogun, score);
	insertInMap(key + "-", idx+1, jogun, score);
}

vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;

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
		insertInMap("", 0, jogun, score);
	}

	
	//"cpp and - and senior and pizza 250"
	for (int i = 0; i < query.size(); ++i) {
		string jogun = "";
		int score;

		string buffer = "";
		for (int j = 0; j < query[i].length(); ++j) {
			if (query[i][j] == ' ') {
				if(buffer != "and") jogun = jogun + buffer;
				buffer = "";
			}
			else buffer += query[i][j];
		}
		score = stoi(buffer);

		//query ���ǿ� �´� �ĺ����� ����
		vector<int> hoobo = m[jogun];
		
		//�������� ����
		sort(hoobo.begin(), hoobo.end());

		//lower_bound = ã������ key ������ ���ų� ū ���ڰ� �迭 �� ��°���� ó�� �����ϴ��� 
		answer.push_back(hoobo.size() - (lower_bound(hoobo.begin(), hoobo.end(), score) - hoobo.begin()));
	}

	return answer;
}

int main() {
	solution({ "java backend junior pizza 150", "python frontend senior chicken 210", "python frontend senior chicken 150", "cpp backend senior pizza 260", "java backend junior chicken 80", "python backend senior chicken 50" }, { "java and backend and junior and pizza 100", "python and frontend and senior and chicken 200", "cpp and - and senior and pizza 250", "- and backend and senior and - 150", "- and - and - and chicken 100", "- and - and - and - 150" });
}