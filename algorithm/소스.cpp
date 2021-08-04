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

	//���ÿ� ���� �Ǵ� ����
	int num = 1;

	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		
		//���� ����ִ� ��� �ϴ� ���� �ϳ� �ֱ�
		if (s.empty()) {
			s.push(num);
			res.push_back('+');
			num++;
		}

		//�Էµ� ������ ������ top ��

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