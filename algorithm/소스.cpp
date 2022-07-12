#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;

int n;
vector<ll> vec;

ll maxAns = -1;

void histogram(int start, int end) {
	if (start > end) return;

	if (start == end) {
		maxAns = max(maxAns, vec[start]);
	}
	if (start + 1 == end) {
		maxAns = max(maxAns, vec[start]);
		maxAns = max(maxAns, vec[end]);
		maxAns = max(maxAns, min(vec[start], vec[end]) * 2);
	}

	int mid = (start + end) / 2;
	
	//vec[mid]를 포함하지 않는 직사각형의 넓이 
	histogram(start, mid-1);
	histogram(mid + 1, end);

	//vec[mid]를 포함하는 직사각형의 넓이 
	maxAns = max(maxAns, vec[mid]);

	ll height = vec[mid];
	ll width = 1;

	int left = mid - 1;
	int right = mid + 1;
	while ((start <= left) || (right <= end)) {
		//두 방향 모두 확장 가능
		if ((start <= left) && (right <= end)) {
			if (min(height, vec[left]) > min(height, vec[right])) {
				height = min(height, vec[left]);
				left--; 
			}
			else {
				height = min(height, vec[right]);
				right++; 
			}
		}
		//왼쪽으로만 확장 가능
		else if (start <= left) {
			height = min(height, vec[left]);
			left--; 
		}
		//오른쪽으로만 확장 가능
		else {
			height = min(height, vec[right]);
			right++; 
		}
		
		width++;
		maxAns = max(maxAns, height * width);
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		ll input;
		cin >> input;
		vec.push_back(input);
	}

	histogram(0, n - 1);
	cout << maxAns;

	return 0;
}