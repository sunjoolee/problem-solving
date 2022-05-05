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

		//m에 삽입 

		//key값 재귀 X 반복 O
		vector<string> keys;
		keys.push_back("");

		vector<string> keysTmp;
		for (int i = 0; i < jogun.size(); ++i) {
			keysTmp.clear();
			for (int j = 0; j < keys.size(); ++j) {
				keysTmp.push_back(keys[j] + jogun[i]);
				keysTmp.push_back(keys[j] + "-");
			}
			keys = keysTmp;
		}

		for (int i = 0; i < keys.size(); ++i) {
			if (m.find(keys[i]) == m.end())
				m[keys[i]] = vector<int>(1, score);
			else
				m[keys[i]].push_back(score);
		}
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

		//query 조건에 맞는 후보들의 점수
		vector<int> hoobo = m[jogun];
		
		//오름차순 정렬
		sort(hoobo.begin(), hoobo.end());

		//lower_bound = 찾으려는 key 값보다 같거나 큰 숫자가 배열 몇 번째에서 처음 등장하는지 
		answer.push_back(hoobo.size() - (lower_bound(hoobo.begin(), hoobo.end(), score) - hoobo.begin()));
	}

	return answer;
}

int main() {
	solution({ "java backend junior pizza 150", "python frontend senior chicken 210", "python frontend senior chicken 150", "cpp backend senior pizza 260", "java backend junior chicken 80", "python backend senior chicken 50" }, { "java and backend and junior and pizza 100", "python and frontend and senior and chicken 200", "cpp and - and senior and pizza 250", "- and backend and senior and - 150", "- and - and - and chicken 100", "- and - and - and - 150" });
}