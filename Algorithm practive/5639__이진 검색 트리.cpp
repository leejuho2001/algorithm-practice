/*
-------------이진 검색 트리 -----------------
기본 아이디어 :
이진 검색 트리의 세가지 조건에 주목해보면 왼쪽 서브트리에 포함된 모든 키들은 루트노드의 키보다 작으며,
오른쪽 서브트리에 포함된 모든 키들은 루트노드의 키보다 크다.

또한 전위순회의 정의를 보면
루트노드 - 왼쪽 서브트리 - 오른쪽 서브트리 순으로 순회를 한다는 것을 알 수 있다.

따라서, 처음으로 루트노드보다 큰 수가 나오는 index의 키가 오른쪽 서브트리의 루트노드의 키이다.
이 점을 이용해서 분할정복 방식을 사용할 수 있다.


시간 복잡도 :
최악의 경우엔 O(n^2)의 시간복잡도를 가지게 되나, 10000개의 노드를 가지기 때문에 최악의 경우에도 약 100000000회의 연산을 거친다.
따라서, 제한시간을 넘길 위험은 거의 없다.



*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int binary_search_tree[10050] = {};

void pre_to_post(int _s, int _e);
int find_right_root(int _s, int _e);

/*
	----pre_to_post----

	설명 : 분할정복 방식을 사용하여 전위순회를 후위순회로 바꾸는 함수.

	(분할정복)
	종료조건 1. 루트노드 = 리프노드 일 경우, 해당 루트노드를 출력하고 종료.
	종료조건 2. 자식노드를 리프노드 하나만 가지는 경우, 리프노드 - 루트노드 순서로 출력하고 종료
	종료조건 3. 모든 자식노드의 출력이 끝났을 경우, 마지막으로 루트노드를 출력하고 종료.

	실행 결과 : 해당 트리의 후위순회 결과가 출력됨.


  param:
	int _s : 해당 전위 순회의 시작지점
	int _e : 해당 전위 순회의 종료지점

*/


void pre_to_post(int _s, int _e) {
	int start = _s, end = _e;
	int root_key = binary_search_tree[start];	

	if (start >= end) {
		printf("%d\n", root_key);
		return;
	} // 종료조건 1. 루트노드 = 리프노드일 경우

	if (end == start + 1) {
		printf("%d\n", binary_search_tree[end]);
		printf("%d\n", root_key);
		return;
	} // 종료조건 2. 자식노드를 리프노드 하나만 가지는 경우


	int root_R = find_right_root(start, end);

	if(root_R > start+1)	pre_to_post(start + 1, root_R - 1); //조건 : 왼쪽 서브트리가 존재하는경우
	if (root_R <= end) pre_to_post(root_R, end); // 조건 : 오른쪽 서브트리가 존재하는경우
	printf("%d\n", root_key);

	// 종료조건 3. 모든 자식노드의 출력이 끝났을 경우

}


/*
	----find_right_root----

	설명 : 해당 루트의 루트노드보다 큰 첫번째 키의 위치를 찾는 함수

	결과 : 오른쪽 자식노드의 루트노드(처음으로 루트노트보다 키가 큰 위치) 를 반환한다.
	만약 더 큰 키가 없는경우 _e + 1을 반환함. 

  param:
	int _s : 해당 전위 순회의 시작지점
	int _e : 해당 전위 순회의 종료지점

*/
int find_right_root(int _s, int _e) {
	int start = _s, end = _e;
	for (int i = start; i <= end; i++) {
		if (binary_search_tree[i] > binary_search_tree[start]) return i;
	}
	return end+1;
}


int main() {
	int key = 1;
	int size = 0;

	while (scanf("%d", &key) != EOF) {
		
		if (key != EOF) {
			binary_search_tree[size] = key;
			size++;
		} //EOF 가 아니라면 트리 배열에 추가하고, 트리의 키 갯수에 ++연산을 해준다.
	}
	pre_to_post(0, size - 1);

}
