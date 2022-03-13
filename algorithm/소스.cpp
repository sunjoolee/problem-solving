#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> notes;

//string으로 주어진 음악 -> 각 음 별로 나누어 int벡터에 저장
vector<int> stringToVec(string music) {
	vector<int> res;

	for (int i = 0; i < music.length(); ++i) {

		if(i + 1 < music.length() && music[i+1] == '#'){
			res.push_back(notes[music.substr(i, 2)]);
			++i;
		}
		else {
			res.push_back(notes[music.substr(i, 1)]);
		}
	}
	return res;
}

//재생된 시간동안 재생된 음악 반환
vector<int> getPlayedMusic(vector<int> music, int playedLen) {
	if (playedLen == music.size()) return music;
	
	vector<int> res;
	for (int i = 0; i < playedLen; ++i) {
		res.push_back(music[i % music.size()]);
	}
	return res;
}


//재생된 음악에 들은 멜로디가 있는지 검사
bool melodyInPlayedMusic(vector<int> music, vector<int> melody) {
	
	if (melody.size() > music.size()) return false;
	if (melody.size() == music.size()) return equal(melody.begin(), melody.end(), music.begin());

	bool in = false;
	for (int i = 0; i < music.size() - melody.size(); ++i) {
		if (equal(melody.begin(), melody.end(), music.begin() + i)) {
			in = true;
			break;
		}
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

string solution(string m, vector<string> musicinfos) {
	
	//12개의 음 int로 매핑
	notes["C"] = 1; notes["C#"] = 2;
	notes["D"] = 3; notes["D#"] = 4;
	notes["E"] = 5;
	notes["F"] = 6; notes["F#"] = 7;
	notes["G"] = 8; notes["G#"] = 9;
	notes["A"] = 10; notes["A#"] = 11;
	notes["B"] = 12;

	vector<int> melody = stringToVec(m);

	//조건에 부합하는 후보 저장 <-재생된 시간, string>
	//재생 시간 내림차순으로 정렬하기 위해 -를 붙여 저장
	vector<pair<int, string>> candidate;

	for (int i = 0; i < musicinfos.size(); ++i) {
		string startTime = "";
		string endTime = "";
		string name = "";
		vector<int> music;

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
		music = stringToVec(buffer);

		//조건에 부합하는지 확인
		int playedTime = getPlayedTime(startTime, endTime);
		vector<int> playedMusic = getPlayedMusic(music, playedTime);

		if (melodyInPlayedMusic(playedMusic, melody)) 
			candidate.push_back({ -playedTime, name });
	}

	//조건에 부합하는 후보 없는 경우 (None)
	if (candidate.empty()) return "(None)";

	//조건에 부합하는 후보 중 가장 길이가 긴 노래 선택
	stable_sort(candidate.begin(), candidate.end());
	string answer = candidate[0].second;

	return answer;
}

int main() {
	solution("A#", {"12:00,12:01,HELLO,A#"});
	return 0;
}