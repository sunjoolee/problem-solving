#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//n: 멀티탭 구멍의 개수
	//k: 전기용품 총 사용 횟수
	int n, k;
	cin >> n >> k;

	//전기용품 사용 순서 
	vector<int> vec;

	//vecmap[전기용품]: 전기용품 사용되는 시점 저장된 queue
	//교체할 전기용품을 선택할 때 가장 나중에 사용되는 전기용품이 무엇인지 보기 위함
	//따라서 전기용품을 사용할 때 queue pop 해줌 
	map<int, queue<int>> vecmap;

	//전기용품 사용 순서 입력 받기
	int num;
	for (int i = 0; i < k; ++i) {
		cin >> num;
		vec.push_back(num);
		
		//전기용품 사용 시점 저장

		if (vecmap.find(num) == vecmap.end())
			vecmap[num] = queue<int>();

		vecmap[num].push(vec.size() - 1);
	}

	//멀티탭에 꽂혀있는 전기용품 
	vector<int> plug;

	//최소 교체 횟수
	int answer = 0;

	//전기용품 사용 순서 순회
	for (int i = 0; i < k; ++i) {
		num = vec[i];
		
		//멀티탭에 꽂혀있는지 확인
		bool flag = false;
		for (int i = 0; i < plug.size(); ++i) {
			if (plug[i] == num) {
				flag = true;
				break;
			}
		}
		//꽂혀있는 경우 그대로 사용
		if (flag) {
			vecmap[num].pop();
			continue;
		}

		//꽂혀있지 않는 경우

		//멀티탭 자리 있으면 꽂는다
		if (plug.size() < n) {
			plug.push_back(num);
			vecmap[num].pop();
			continue;
		}

		//멀티탭 자리 없으면 전기용품 교체해야함

		//가장 나중에 사용되는 전기용품의 멀티탭 위치
		int maxIdx = 0;
		//가장 나중에 사용되는 전기용품의 사용되는 시점 
		int maxpos = -1;

		//멀티탭에 꽂혀있는 전기용품 중 가장 나중에 사용되는 것 찾기
		for (int i = 0; i < plug.size(); ++i) {

			//전기용품의 사용되는 시점
			//만약 앞으로 전기용품이 사용될 예정이 없다면 k로 설정 
			int pos;
			if (vecmap[plug[i]].empty()) {
				pos = k;
			}
			else pos = vecmap[plug[i]].front();

			if (pos > maxpos) {
				maxpos = pos;
				maxIdx = i;
			}
		}

		//가장 나중에 사용되는 전기용품을 교체
		// -> 가장 나중에 사용되는 전기용품의 멀티탭 위치에 꽂는다 
		plug[maxIdx] = num;
		vecmap[num].pop();

		++answer;
	}

	cout << answer;
	return 0;
}