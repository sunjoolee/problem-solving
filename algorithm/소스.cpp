#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int height;
	cin >> height;

	int numofnodes = pow(2, height + 1) - 1;

	string path;
	cin >> path;

	//경로가 주어지지 않은 경우
	if (cin.eof()) {
		//루트의 노드 번호 출력 후 종료
		cout << numofnodes;
		return 0;
	}

	
	int i = 1;
	for (int j = 0; j < path.size(); ++j) {
		//LeftChild로 이동
		if (path[j] == 'L') 
			i = 2 * i;
		//RightChild로 이동
		else if (path[j] == 'R') 
			i = 2 * i + 1;
	}

	//경로의 도착 지점의 노드 번호 출력
	cout << numofnodes - i + 1;

	return 0;
}