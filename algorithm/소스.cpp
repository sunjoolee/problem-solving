#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//string���� �־��� ���� -> �� �� ���� ������ ���Ϳ� ����
vector<string> musicToVec(string music) {
	
	vector<string> res;
	for (int i = 0; i < music.length(); ++i) {
		char note = music[i];

		if (note != '#') {
			res.push_back(to_string(note));
		}
		else {
			string prevNote = res.back();
			res.pop_back();

			res.push_back(prevNote + to_string(note));
		}
	}
	return res;
}

//����� �ð����� ����� ���� ��ȯ
vector<string> getPlayedMusic(vector<string> music, int playedLen) {
	if (playedLen == music.size()) return music;
	
	vector<string> res;
	for (int i = 0; i < playedLen; ++i) {
		res.push_back(music[i % music.size()]);
	}
	return res;
}

//����� ���ǿ� ���� ��ε� �ִ��� �˻�
bool melodyInPlayedMusic(vector<string> music, vector<string> melody) {
	
	if (melody.size() > music.size()) return false;

	bool in = false;
	for (int i = 0; i < music.size() - melody.size(); ++i) {
		bool flag = true;
		for (int j = 0; j < melody.size(); ++j) {
			if (music[i + j] != melody[j]) {
				flag = false;
				break;
			}
		}
		if (flag) in = true;
	}
	return in;
}

//����� �ð� ���
int getPlayedTime(string startTime, string endTime) {
	//HH:MM
	int start = stoi(startTime.substr(0, 2)) * 60 + stoi(startTime.substr(3, 2));
	int end = stoi(endTime.substr(0, 2)) * 60 + stoi(endTime.substr(3, 2));
	
	return end - start;
}

bool cmp(pair<string, int> a, pair<string, int> b) {
	return a.second > b.second;
}

string solution(string m, vector<string> musicinfos) {
	
	vector<string> melody = musicToVec(m);

	//���ǿ� �����ϴ� �ĺ� <����, ����� �ð�>
	vector<pair<string, int>> candidate;

	for (int i = 0; i < musicinfos.size(); ++i) {
		string startTime = "";
		string endTime = "";
		string name = "";
		string music = "";

		//musicinfos �Ľ�
		string buffer = "";
		for (int j = 0; j < musicinfos[i].size(); ++j) {
			char ch = musicinfos[i][j];
			if (ch == ',') {
				if (startTime == "") startTime = buffer;
				else if (endTime == "") endTime = buffer;
				else if (name == "") name = buffer;

				buffer = "";
			}
			else buffer += ch;
		}
		music = buffer;

		//���ǿ� �����ϴ��� Ȯ��
		int playedTime = getPlayedTime(startTime, endTime);
		vector<string> playedMusic = getPlayedMusic(musicToVec(music), playedTime);

		if (melodyInPlayedMusic(playedMusic, melody)) 
			candidate.push_back({ name, playedTime });
	}

	//���ǿ� �����ϴ� �ĺ� ���� ��� (None)
	if (candidate.empty()) return "(None)";

	//���ǿ� �����ϴ� �ĺ� �� ���� ���̰� �� �뷡 ����
	stable_sort(candidate.begin(), candidate.end(), cmp);
	string answer = candidate[0].first;

	return answer;
}

int main() {
	solution("ABC", { "12:00,12:14,HELLO,C#DEFGAB", "13:00,13:05,WORLD,ABCDEF" });
	return 0;
}