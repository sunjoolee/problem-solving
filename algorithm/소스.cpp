#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<string> words) {

	int N = words.size();

	int answer = 0;

	//다른 단어와 공통된 접미사가 있는 경우, 접미사가 끝나는 지점의 인덱스 저장
	vector<int> maxPrefix(N, -1);

	for (int i = 0; i < words.size(); ++i) {
		//검색 범위
		//공통된 접두사를 가진 단어들 사이에서만 재검색되도록 검색 범위 계속 갱신해주기 
		//맨 처음에는 모든 단어가 검색 범위에 해당됨
		vector<bool> searchRange(N, true);

		//공통된 접미사를 갖는 단어만 검색 범위에 들도록 함 
		if (maxPrefix[i] != -1) {
			for (int j = 0; j < N; ++j) {
				if (words[j].length() <= maxPrefix[i])
					searchRange[j] = false;
				else if (words[i].substr(0, maxPrefix[i] + 1) != words[j].substr(0, maxPrefix[i] + 1))
					searchRange[j] = false;
			}
		}
		
		//공통된 최대 길이 접미사 이후의 단어부터 비교
		if(maxPrefix[i] != -1) 
			answer += maxPrefix[i];
		
		for (int j = maxPrefix[i] + 1; j < words[i].length(); ++j) {
			char searchWord = words[i][j];
			answer++;

			//search 문자열로 검색했을 때 검색 결과가 하나만 반환되는지 검사
			//이 검색 결과에 포함되는 경우 다음 검색 때 검색 범위로 사용함
			int searchCnt = 1;
			for (int k = 0; k < N; ++k) {
				//자기 자신 스킵
				if (k == i) continue;

				//검색 범위에 포함된 단어인 경우 검사
				if (searchRange[k]) {
					if (words[k].length() > j && words[k][j] == searchWord) {
						searchCnt++;

						//words[k]와 words[i]는 문자열의 인덱스 0~j까지 공통된 접미사를 가진다는 의미
						maxPrefix[i] = j;
						maxPrefix[k] = max(maxPrefix[k],j);
					}
					//검색 결과에 포함되지 않으면 검색 범위에서 제외
					else searchRange[k] = false;
				}
			}
			if (searchCnt == 1) break;
		}
	}
	
	return answer;
}

int main() {
	solution({ "go", "gone", "guild" });
}