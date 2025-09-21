/*
	---- 15663_N과M (9) ----

	아이디어 : 
	이번 문제의 핵심은 한 숫자가 두 번 이상 등장할 수 있다는 것이며,
	같은 숫자끼리는 순서를 따지지 않는다.
	때문에, 중복되는 수열들은 모두 제거해주어야하는 형태의 문제이다.

	기존에는 배열에 숫자를 저장하는 방식을 사용했는데, 이 경우엔 배열에 숫자가 두 개가 들어갈 수 있고,
	그렇게 될 경우 순서를 반대로 사용할 수 있게된다.

	따라서, 이를 방지하기 위해 1개의 원소를 사용할 수 있는 횟수 의 형태로 저장한다.

	ex) 9 4 1 9 는 1, 4, 9 로 저장되며, 각각 1회, 1회, 2회 사용할 수 있다.

	이렇게 될 경우, 하나의 숫자가 두 개 이상 들어가더라도 중복되는 수열이 발생하지 않는다.
	몇개가 들어갔는가? 만 따지면 되기 때문이다.

	따라서 다음과 같은 변경점이 발생한다.

	저장하는 자료형 : int 형 -> key, quantity 값을 가지는 struct
	DT의 조건 : DT가 true인가? -> DT의 값이 quantity값보다 큰가?

	그리고 이와 같은 변경점을 반영한 Backtracking을 통해 문제를 해결한다.

*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<algorithm>

using namespace std;

typedef struct _number {
	int key;
	int quantity;
}number;

int N, M;
int arraySize;
number numberArr[10];
int address[10];
int DT[10];

bool comp(number a, number b) {
	return a.key < b.key;
}

/*
	---- input ----
	param : 없음

	역할 : 
	1. int형 수를 temp에 저장한다.
	2. temp에 저장된 값이 numberArr 내에 있는지 확인한다.
	3-1. 있을경우 해당 항목의 quantity를 1 늘린다.
	3-2. numberArr에 없을경우 arraySize를 1 올리고, 끝index에 새로운 정보를 넣어준다.
*/
void input() {
	arraySize = 0;
	for (int _ = 0; _ < N; _++) {
		bool flag = false;
		int temp;
		scanf("%d", &temp);
		for (int i = 0; i < arraySize; i++) {
			if (numberArr[i].key == temp) { 
				numberArr[i].quantity++; 
				flag = true;
				break;
			}
		}
		if (flag == false) {
			numberArr[arraySize] = { temp, 1 };
			arraySize++;
		}
	}
}

/*
	---- backTracking ----
	param
	_index : 현재 탐색할 칸의 순서
	_level : 배정한 원소의 갯수 (level 3: 3개 배정함)

	종료조건 :
	1. _level == m일때
	==> address에 저장되어있는 모든 값을 인쇄한 뒤 백트래킹

	변경점 : DT에 저장된 정수가 numberArr에 저장된 quantity보다 작은가?
	로 탐색 범위를 설정함.
*/

void backTracking(int _index, int _level) {
	int index = _index;
	int level = _level;

	if (level > 0) {
		DT[index]++;
		address[level] = numberArr[index].key;
	}

	if (level == M) {
		for (int i = 1; i <= M; i++)
			printf("%d ", address[i]);

		puts("");

	}

	else {
		for (int slot = 0; slot < arraySize; slot++) {
			if (DT[slot] < numberArr[slot].quantity) {
				backTracking(slot, level + 1);
			}
		}
	}

	if (level > 0) {
		DT[index]--;
		address[level] = 0;
	} //백트래킹

}

int main() {
	scanf("%d %d", &N, &M);

	input();
	sort(numberArr, numberArr + arraySize, comp);

	backTracking(-1, 0);
}



