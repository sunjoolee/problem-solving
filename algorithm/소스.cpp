#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int A, B;
	cin >> A >> B;

	int L = 0;
	int R = 0;

	//목적지에서 루트로 거슬러 올라간다
	while (A > 1 && B > 1) {
		if (A > B) {
			A = A - B;
			L++;
		}
		else {
			B = B - A;
			R++;
		}
	}

	//A가 1이 된 경우 R을 따라 (1,1)까지 쭉 올라간다
	if (A == 1)
		R += (B - 1);

	//B가 1이 된 경우 L을 따라 (1,1)까지 쭉 올라간다
	else if (B == 1)
		L += (A - 1);

	cout << L <<" "<<R;
	return 0;
}