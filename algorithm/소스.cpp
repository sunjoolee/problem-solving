#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int solution(vector<string> words) {
	int answer = 0;
	for (int i = 0; i < words.size(); ++i) {
		
		//�ش� �ܾ �˻��ϱ� ���� ����ؾ��ϴ� ���ڿ�
		//searchWord �� ���ھ� append ���ָ� �����ش�
		//�ʿ�� ������ �˰��� �� ���ظ� ���� �������
		string search = "";

		//�˻� ����
		//����� ���λ縦 ���� �ܾ�� ���̿����� ��˻��ǵ��� �˻� ���� ��� �������ֱ� 
		vector<string> searchRange(words.begin(), words.end());
		
		for (int j = 0; j < words[i].length(); ++j) {
			char searchWord = words[i][j];
			search.append(to_string(searchWord));
			answer++;

			//search ���ڿ��� �˻����� �� �˻� ����� �ϳ��� ��ȯ�Ǵ��� �˻�
			//�� �˻� ����� ���� �˻� �� �˻� ������ �����
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