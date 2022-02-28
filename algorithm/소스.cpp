#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<int, char> intToChar;

string numToString(int n, int num) {
	string str = "";
	while (num > 0) {
		str += intToChar[num % n];
		num /= n;
	}
	return str;
}

string solution(int n, int t, int m, int p) {
	//1번째 사람이 0번째 순서를 갖도록 함
	p--;
	
	//map 초기화
	intToChar[0] = '0';
	intToChar[1] = '1';
	intToChar[2] = '2';
	intToChar[3] = '3';
	intToChar[4] = '4';
	intToChar[5] = '5';
	intToChar[6] = '6';
	intToChar[7] = '7';
	intToChar[8] = '8';
	intToChar[9] = '9';
	intToChar[10] = 'A';
	intToChar[11] = 'B';
	intToChar[12] = 'C';
	intToChar[13] = 'D';
	intToChar[14] = 'E';
	intToChar[15] = 'F';

	string game = "0";
	int num = 1;
	while (game.length() < p + (t * m)) {
		game += numToString(n, num);
		num++;
	}

	string answer = "";
	for (int i = 0; i < t; ++i) {
		answer += game[p + (i * m)];
	}
	
	return answer;
}

int main() {
	solution(2, 4, 2, 1);
}