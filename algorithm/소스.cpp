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

	//�̸��� ����
	vector <int> name;

	string input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		name.push_back(input.size());
	}
	
	
	long long cnt = 0;
	for (int len = 2; len <= 20; ++len) {
		//���� �� �̸��� ���̰� len�� �л��� ��
		long long rangecnt = 0;
		for (int i = 0; i < k; ++i)
			if (name[i] == len) rangecnt++;

		//�����̵� ������
		for (int i = 0; i < n; ++i) {
			if (i + k < n && name[i + k] == len) rangecnt++;
			if (name[i] == len) {
				rangecnt--;
				cnt += rangecnt;
			}
		}
	}
	
	cout << cnt;
	return 0;
}