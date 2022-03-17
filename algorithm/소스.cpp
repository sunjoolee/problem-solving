#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

vector<string> solution(vector<string> record) {

	//<uID, name>
	map<string, string> m;
	//<Enter 0/Leave 1, uID> 
	queue<pair<int, string>> q;

	for (int i = 0; i < record.size(); ++i) {
		vector<string> rec;

		string buffer = "";
		for (int j = 0; j < record[i].length(); ++j) {
			if (record[i][j] == ' ') {
				rec.push_back(buffer);
				buffer = "";
			}
			else buffer += record[i][j];
		}
		rec.push_back(buffer);

		if (rec[0] == "Enter") {
			m[rec[1]] = rec[2];
			q.push({ 0, rec[1] });
		}
		if (rec[0] == "Leave") {
			q.push({ 1, rec[1] });
		}
		if (rec[0] == "Change") {
			m[rec[1]] = rec[2];
		};
	}

	vector<string> answer;
	while (!q.empty()) {
		int flag = q.front().first;
		string uId = q.front().second;
		q.pop();

		if (flag == 1) {
			string ans = m[uId] + "님이 들어왔습니다.";
			answer.push_back(ans);
		}
		else {
			string ans = m[uId] + "님이 나갔습니다.";
			answer.push_back(ans);
		}
	}
	return answer;
}

int main() {
	solution({ "Enter uid1234 Muzi", "Enter uid4567 Prodo", "Leave uid1234", "Enter uid1234 Prodo", "Change uid4567 Ryan" });
}