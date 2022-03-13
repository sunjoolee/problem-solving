#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int solution(vector<string> words) {
	int answer = 0;
	for (int i = 0; i < words.size(); ++i) {
		
		//해당 단어를 검색하기 위해 사용해야하는 문자열
		//searchWord 한 글자씩 append 해주며 구해준다
		//필요는 없지만 알고리즘 논리 이해를 위해 계산해줌
		string search = "";

		//검색 범위
		//공통된 접두사를 가진 단어들 사이에서만 재검색되도록 검색 범위 계속 갱신해주기 
		vector<string> searchRange(words.begin(), words.end());
		
		for (int j = 0; j < words[i].length(); ++j) {
			char searchWord = words[i][j];
			search.append(to_string(searchWord));
			answer++;

			//search 문자열로 검색했을 때 검색 결과가 하나만 반환되는지 검사
			//이 검색 결과를 다음 검색 때 검색 범위로 사용함
			vector<string> searchResult;
			for (int k = 0; k < searchRange.size(); ++k) {
				if (searchRange[k][0] == searchWord) {
					searchResult.push_back(searchRange[k].substr(1));
				}
			}

			if (searchResult.size() == 1) break;
			
			searchRange.clear(); 
			searchRange.assign(searchResult.begin(), searchResult.end());
		}
	}
	
	return answer;
}

int main() {
	solution({ "go", "gone", "guild" });
}