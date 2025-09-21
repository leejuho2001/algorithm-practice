#define _CRT_SECURE_NO_WARNINGS

/*
	---- 15654_N과 M(5) ----

	단순 구현 문제
	sort 문제는 별도의 모듈을 통해 해결.
	모두 다른 숫자를 가지고 있으므로, 겹치는 경우만 예외처리하면 됨.

	m진수의 증가를 구현함.
	1. 맨끝자리의 수를 +1
	2. 맨끝자리의 수가 m을 넘어간다면 맨끝자리수를 0으로 만들고 그 앞자리수 +1
	3. 2번의 받아올림과정을 모든 자리에 대해 역순으로 진행

	== 시간초과
	왜 시간초과인가 ? -> 시간복잡도가 O(n^n)이기 때문.
	따라서 8자리인 경우 8^8이 되는데, 이때문에 연산의 수가 매우 많아지게 된다.

	:: 해결방법(방법 2) : backtracking+dynamic programing을 사용한다.
	특정 조건을 만족하지 않는 탐색을 아예 실행하지 않음으로써
	연산의 양을 크게 줄일 수 있음.
	*/
#include<stdio.h>
#include<algorithm>
using namespace std;
/*
int n, m;
int numbers[10];
int address[10];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", &numbers[i]);
	sort(numbers, numbers + n);
	for (int i = 0; i < m; i++) address[i] = 0;
	while (address[0] < n) {
		bool flag = false;
		for (int i = 1; i < m; i++) {
			for(int j=0;j<i;j++){ 
				if (address[i] == address[j]) {
					flag = true;
					break;
				}
			}
			if (flag == true) break;
		}
		//중복 없는지 체크

		if (flag == false) {
			for (int i = 0; i < m; i++)printf("%d ", numbers[address[i]]);
			puts("");
		}

		//없다면 출력
		address[m - 1] ++;
		for (int q = m - 1; q > 0; q++) {
			if (address[q] < n) break;
			address[q] = 0;
			address[q - 1]++;
		}
	}
}
*/
// 방법 1 (시간초과)

int n, m;
int numbers[10];
int address[10];
bool slotDT[10]; // 몇번 index의 숫자가 사용되었는가? 를 확인함.

/*
	---- backTracking ----
	입력값
	_index : 현재 탐색할 칸의 순서
	_level : 배정한 원소의 갯수 (level 3: 3개 배정함)

	종료조건 :
	1. _level == m일때
	==> address에 저장되어있는 모든 값을 인쇄한 뒤 백트래킹
*/

void backTracking(int _index, int _level) {
	int index = _index;
	int level = _level;

	if (level > 0) {
		slotDT[index] = true;
		address[level] = numbers[index];
	}

	if (level == m) {
		for (int i = 1; i <= m; i++)
			printf("%d ", address[i]);

		puts("");
		
	}

	else {
		for (int slot = 0; slot < n; slot++) {
			if (slotDT[slot] == false) {
				backTracking(slot, level + 1);
			}
		}
	}

	if (level > 0) {
		slotDT[index] = false;
		address[level] = numbers[index];
	} //백트래킹

}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", numbers + i);
	}

	sort(numbers, numbers + n);

	backTracking(-1, 0);
}