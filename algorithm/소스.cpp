#include <string>
#include <vector>

using namespace std;


string solution(vector<int> numbers, string hand) {

	string answer = "";

	//번호 간 거리 초기화 (* : 13, # : 14)
	vector<vector<int>> dist(15, vector<int>(15, 0));

	dist[1][2] = dist[3][2] = 1;
	dist[1][5] = dist[3][5] = 2;
	dist[1][8] = dist[3][8] = 3;
	dist[1][0] = dist[3][0] = 4;

	dist[4][2] = dist[6][2] = 2;
	dist[4][5] = dist[6][5] = 1;
	dist[4][8] = dist[6][8] = 2;
	dist[4][0] = dist[6][0] = 3;

	dist[7][2] = dist[9][2] = 3;
	dist[7][5] = dist[9][5] = 2;
	dist[7][8] = dist[9][8] = 1;
	dist[7][0] = dist[9][0] = 2;

	dist[13][2] = dist[14][2] = 4;
	dist[13][5] = dist[14][5] = 3;
	dist[13][8] = dist[14][8] = 2;
	dist[13][0] = dist[14][0] = 1;

	//center
	dist[2][2] = dist[5][5] = dist[8][8] = dist[0][0] = 0;
	dist[2][5] = dist[5][2] = dist[5][8] = dist[8][5] = dist[0][8] = dist[8][0] = 0;
	dist[2][8] = dist[8][2] = dist[5][0] = dist[0][5] = 2;
	dist[2][0] = dist[0][2] = 3;


	//현재 엄지 손가락의 위치
	int Lpos = 13; //*
	int Rpos = 14; //#

	for (int i = 0; i < numbers.size(); ++i) {
		int num = numbers[i];
		if (num == '*') num = 13;
		if (num == '#') num = 14;

		//flag = 0 왼손, flag = 1 오른손
		int flag;

		if (num == 1 || num == 4 || num == 7 || num == 13) flag = 0;
		else if (num == 3 || num == 6 || num == 9 || num == 14) flag = 1;

		else {
			if (dist[Lpos][num] < dist[Rpos][num]) flag = 0;
			else if (dist[Lpos][num] > dist[Rpos][num]) flag = 1;
			else if (hand == "left") flag = 0;
			else flag = 1;
		}

		//손가락 움직이기
		if (flag){
			Rpos = num;
			answer += "R";
		}
		else {
			Lpos = num;
			answer += "L";
		}
	}
	return answer;
}