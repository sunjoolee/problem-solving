#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int N;

void recursion(int n) {
	if (n == N) {
		for (int i = 0; i < n; ++i) cout << "____";
		cout << "\"����Լ��� ������?\""<<"\n";

		for (int i = 0; i < n; ++i) cout << "____";
		cout << "\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"" << "\n";
			

		for (int i = 0; i < n; ++i) cout << "____";
		cout << "��� �亯�Ͽ���." << "\n";

		return;
	}

	for (int i = 0; i < n; ++i) cout << "____";
	cout << "\"����Լ��� ������?\"" << "\n";

	for (int i = 0; i < n; ++i) cout << "____";
	cout << "\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���." << "\n";
		
	for (int i = 0; i < n; ++i) cout << "____"; 
	cout << "���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���." << "\n";
		
	for (int i = 0; i < n; ++i) cout << "____"; 
	cout << "���� ���� ��κ� �ǾҴٰ� �ϳ�.�׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"" << "\n";
		
	recursion(n + 1);

	for (int i = 0; i < n; ++i) cout << "____";
	cout << "��� �亯�Ͽ���." << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	cout << "��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������.\n";
	
	recursion(0);

	return 0;
}