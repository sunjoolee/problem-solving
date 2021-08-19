#include <iostream>
#include <cmath>
using namespace std;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int A, B, V;
	cin >> A >> B >> V;

	//�������� ��ġ���� ������� ���� ���̰� A ������ �� 
	//������ ���� ������ �� �ִ� 
	
	// x��° ���� ����� �� ������ ��ġ = (A - B) * x	
	// V - A <= (A - B) * x
	// (V - A) / (A - B) <= x

	cout << (int)ceil((double)(V - A) / (A - B)) + 1;
	return 0;
}