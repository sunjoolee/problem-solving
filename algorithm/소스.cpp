#include <iostream>
#include <stack>
#include <vector>
using namespace std;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n;
	cin >> n;

	stack<int> s;
	vector<char> res;

	//스택에 들어가게 되는 숫자
	int num = 1;

	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		
		//스택 비어있는 경우 일단 숫자 하나 넣기
		if (s.empty()) {
			s.push(num);
			res.push_back('+');
			num++;
		}

		//입력된 수열과 스택의 top 비교

		if (input < s.top()) {
			cout << "NO";
			return 0;
		}

		while (input > s.top()) {
			s.push(num);
			res.push_back('+');
			num++;
		}

		if (input == s.top()) {
			s.pop();
			res.push_back('-');
		}
	}

	for (int i = 0; i < res.size(); ++i)
		cout << res[i] << "\n";

	return 0;
}