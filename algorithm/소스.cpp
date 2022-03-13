#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//string으로 주어진 음악 -> 각 음 별로 나누어 벡터에 저장
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

//재생된 시간동안 재생된 음악 반환
vector<string> getPlayedMusic(vector<string> music, int playedLen) {
	if (playedLen == music.size()) return music;
	
	vector<string> res;
	for (int i = 0; i < playedLen; ++i) {
		res.push_back(music[i % music.size()]);
	}
	return res;
}

//재생된 음악에 들은 멜로디가 있는지 검사
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

//재생된 시간 계산
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

	//조건에 부합하는 후보 <제목, 재생된 시간>
	vector<pair<string, int>> candidate;

	for (int i = 0; i < musicinfos.size(); ++i) {
		string startTime = "";
		string endTime = "";
		string name = "";
		string music = "";

		//musicinfos 파싱
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

		//조건에 부합하는지 확인
		int playedTime = getPlayedTime(startTime, endTime);
		vector<string> playedMusic = getPlayedMusic(musicToVec(music), playedTime);

		if (melodyInPlayedMusic(playedMusic, melody)) 
			candidate.push_back({ name, playedTime });
	}

	//조건에 부합하는 후보 없는 경우 (None)
	if (candidate.empty()) return "(None)";

	//조건에 부합하는 후보 중 가장 길이가 긴 노래 선택
	stable_sort(candidate.begin(), candidate.end(), cmp);
	string answer = candidate[0].first;

	return answer;
}

int main() {
	solution("ABC", { "12:00,12:14,HELLO,C#DEFGAB", "13:00,13:05,WORLD,ABCDEF" });
	return 0;
}