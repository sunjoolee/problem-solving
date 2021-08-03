#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	string input;
	cin >> input;

	//지금까지 나온 사과의 번호
	int appleNo = 0;
	//지금까지 나온 사과를 이진수와 대응시키기 위해 사용하는 스택
	stack<int> apple;

	//appleTree[i]: 이진수의 i번째 자리와 대응되는 사과의 번호
	vector<int> appleTree;

	for (int i = 0; i < 2 * n; ++i) {
		if (input[i] == '0') {
			//새로운 사과 방문 -> 스택에 저장
			apple.push(appleNo);
			appleTree.push_back(appleNo);

			appleNo++;
		}

		if (input[i] == '1') {
			//기존의 사과에서 리턴 -> 스택에서 pop
			appleTree.push_back(apple.top());
			apple.pop();
		}
	}

	//applePair[i]: <사과 i를 방문할 때의 이진수에서의 0의 위치,사과 i에서 리턴될 때의 이진수에서의 1의 위치> 
	vector<pair<int, int>> applePair(n, make_pair(0,0));
	
	for (int i = 0; i < 2 * n; ++i) {
		int curapple = appleTree[i];
		//curapple 사과를 방문할 때의 이진수에서의 0의 위치
		if (input[i] == '0')
			applePair[curapple].first = i;
		//curapple 사과에서 리턴할 때의 이진수에서의 1의 위치
		if (input[i] == '1')
			applePair[curapple].second = i;
	}

	//썩은 사과
	int x, y;
	cin >> x >> y;
	
	//썩은 사과가 이진수에서 처음으로 나타난 위치 
	int badappleStart = min(applePair[appleTree[x-1]].first, applePair[appleTree[y-1]].first);
	//썩은 사과가 이진수에서 마지막으로 나타난 위치
	int badappleEnd = max(applePair[appleTree[x-1]].second, applePair[appleTree[y-1]].second);

	int ansi = 0;
	int ansj = 2*n-1;

	for (int i = 0; i < n; ++i) {
		if ((applePair[i].first <= badappleStart) && (applePair[i].second >= badappleEnd)) {
			if (applePair[i].first >= ansi) {
				ansi = applePair[i].first;
				ansj = applePair[i].second;
			}
		}
	}

	cout << ansi+1 << " " << ansj+1;
	return 0;
}