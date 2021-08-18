#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const ull MAX_TIME = (ull)2000000000 * (ull)30;

int N, M;
int durtime[10001];

int main(void){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < M; i++)
		cin >> durtime[i];

	//��� ���� ���̱ⱸ ������ �۰ų� ���� ���
	//���̱ⱸ ��ȣ�� ���� �� ���� �ϳ��� ���ʴ�� ž���Ѵ�
	if (N <= M){
		cout << N;
		return 0;
	}

	//N���� ����� ��� ���̱ⱸ�� ž���ϰ� �Ǵ� �ּ� �ð� (�̺� Ž��)
	ull minTime = MAX_TIME;

	ull low = 0;
	ull high = MAX_TIME;
	for (int it = 0; it < 100; ++it) {
		ull mid = (low + high) / 2;

		//���� ����: x�е��� N���� ����� ���̱ⱸ�� ž���� �� �ִ°�?
		//0�ʿ� ��� ���̱ⱸ�� �� ����� ž���ϹǷ� cnt = M���� ����
		ull cnt = M;
		for (int i = 0; i < M; i++)
			cnt += mid / durtime[i];

		if (cnt >= N) {
			minTime =min(minTime, mid);
			high = mid;
		}
		else low = mid;
	}

	//������ ����� Ÿ�� ���̱ⱸ�� ��ȣ ���ϱ�!
	
	//minTime - 1 �ð����� ���̱ⱸ�� ž���ϰ� �Ǵ� ��� ��
	ull cnt = M;
	for (int i = 0; i < M; i++) 
		cnt += (minTime - 1) / durtime[i];
	

	// minTime �ð��� ���̱ⱸ�� ž���ϰ� �Ǵ� ��� ��
	for (int i = 0; i < M; i++){
		if (minTime % durtime[i] == 0)
			++cnt;

		if (cnt == N){
			cout << i + 1;
			return 0;
		}
	}

	return 0;
}
