#include <iostream>
#include <cmath>
using namespace std;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int A, B, V;
	cin >> A >> B >> V;

	//달팽이의 위치에서 정상까지 남은 높이가 A 이하일 때 
	//다음날 정상에 도착할 수 있다 
	
	// x번째 날이 종료된 후 달팽이 위치 = (A - B) * x	
	// V - A <= (A - B) * x
	// (V - A) / (A - B) <= x

	cout << (int)ceil((double)(V - A) / (A - B)) + 1;
	return 0;
}