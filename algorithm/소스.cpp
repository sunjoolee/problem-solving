#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> notes;

//string���� �־��� ���� -> �� �� ���� ������ int���Ϳ� ����
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

//����� �ð����� ����� ���� ��ȯ
vector<int> getPlayedMusic(vector<int> music, int playedLen) {
	if (playedLen == music.size()) return music;
	
	vector<int> res;
	for (int i = 0; i < playedLen; ++i) {
		res.push_back(music[i % music.size()]);
	}
	return res;
}


//����� ���ǿ� ���� ��ε� �ִ��� �˻�
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

//����� �ð� ���
int getPlayedTime(string startTime, string endTime) {
	//HH:MM
	int start = stoi(startTime.substr(0, 2)) * 60 + stoi(startTime.substr(3, 2));
	int end = stoi(endTime.substr(0, 2)) * 60 + stoi(endTime.substr(3, 2));
	
	return end - start;
}

string solution(string m, vector<string> musicinfos) {
	
	//12���� �� int�� ����
	notes["C"] = 1; notes["C#"] = 2;
	notes["D"] = 3; notes["D#"] = 4;
	notes["E"] = 5;
	notes["F"] = 6; notes["F#"] = 7;
	notes["G"] = 8; notes["G#"] = 9;
	notes["A"] = 10; notes["A#"] = 11;
	notes["B"] = 12;

	vector<int> melody = stringToVec(m);

	//���ǿ� �����ϴ� �ĺ� ���� <-����� �ð�, string>
	//��� �ð� ������������ �����ϱ� ���� -�� �ٿ� ����
	vector<pair<int, string>> candidate;

	for (int i = 0; i < musicinfos.size(); ++i) {
		string startTime = "";
		string endTime = "";
		string name = "";
		vector<int> music;

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
		music = stringToVec(buffer);

		//���ǿ� �����ϴ��� Ȯ��
		int playedTime = getPlayedTime(startTime, endTime);
		vector<int> playedMusic = getPlayedMusic(music, playedTime);

		if (melodyInPlayedMusic(playedMusic, melody)) 
			candidate.push_back({ -playedTime, name });
	}

	//���ǿ� �����ϴ� �ĺ� ���� ��� (None)
	if (candidate.empty()) return "(None)";

	//���ǿ� �����ϴ� �ĺ� �� ���� ���̰� �� �뷡 ����
	stable_sort(candidate.begin(), candidate.end());
	string answer = candidate[0].second;

	return answer;
}

int main() {
	solution("A#", {"12:00,12:01,HELLO,A#"});
	return 0;
}