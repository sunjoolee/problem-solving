#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
using namespace std;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n; //주차공간의 수
	int m; //차량 수
	vector<int> R; //주차공간 별 주차 요금
	vector<int> W; //차량 무게


	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		int r;
		cin >> r;
		R.push_back(r);
	}
	for (int i = 0; i < m; ++i) {
		int w;
		cin >> w;
		W.push_back(w);
	}


	//주차장 앞 큐
	queue<int> q;

	//parkinglot[n]: n번 주차공간 비어있으면 0, 차있으면 1
	vector<int> parkinglot(n, 0);

	//carParked[m]: m번 차가 주차되어있는 주차공간 번호
	map<int, int> carParked;

	int pay = 0;
	for (int i = 0; i < (2 * m); ++i) {
		int car;
		cin >> car;

		//차가 들어오는 경우
		if (car > 0) {
			car--;
			
			bool parked = false;
			//빈 주차공간 찾아서 주차
			for (int p = 0; p < n; ++p) {
				if (parkinglot[p] == 0) {
					carParked[car] = p;
					parkinglot[p] = 1;
					parked = true;
					break;
				}
			}

			//빈 주차공간 없는 경우 큐에서 대기
			if(!parked) q.push(car);
		}

		//차가 나가는 경우
		else {
			car = car * (-1);
			car--;

			//주차요금 계산
			int p = carParked[car];
			pay += (R[p] * W[car]);

			//주차장에서 나감
			carParked.erase(car);
			parkinglot[p] = 0;

			//큐에 대기 중인 차 있는 경우
			if (!q.empty()) {

				//빈 주차공간 있다면 찾아서 주차
				for (int p = 0; p < n; ++p) {
					if (parkinglot[p] == 0) {
						carParked[q.front()] = p;
						parkinglot[p] = 1;
						q.pop();
						break;
					}
				}
			}
		}
	}

	cout << pay;
	return 0;
}