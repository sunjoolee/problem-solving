#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);


	int n, k;
	cin >> n >> k;

	//�̸� ����
	vector <int> name;

	string input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		name.push_back(input.size());
	}
	
	//���� ģ�� ��
	int cnt = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 1; j <= k && i + j < n; j++)
			if (name[i] == name[i + j])
				cnt++;
	
	cout << cnt;
	return 0;
}