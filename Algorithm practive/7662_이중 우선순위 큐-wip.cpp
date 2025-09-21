#define _CRT_SECURE_NO_WARNINGS
/*
	---- 7662_이중 우선순위 큐 ----

	기본 아이디어 : Priority Queue는 힙을 통해 구현된다
	힙 : 층이 높을수록 크거나, 작아지는 등 계층구조를 가지는 트리

	따라서, Priority를 보관하는 자료형을 하나 만들어서 해당 자료형으로 정보를 저장하고 힙에 Push / pop 하는 방식으로 구현한다.
	이중 Priority Queue 이므로, 최소힙과 최대힙 둘 다 사용해야 한다. 
	다만, 위 문제에선 정수만 입력받으므로, 정수의 크기 자체를 Priority로 사용한다.

	핵심 문제: 최소 / 최대 힙에서 pop 하는 연산을 했을 때, 반대 힙에서 원소를 어떻게 뺄 / 뺀 것으로 취급할 것인가?
*/

#include<stdio.h>

int min_heap[1000050];
int MAX_heap[1000050];
// Priority Queue를 구현하기 위해 사용할 두 개의 힙.
// 0번 위치엔 size를 저장하고 나머지를 값을 저장하는 데 사용한다.
// 일단 확장성을 배제하고 구현을 시작한다.


/*
	---- swap ----
	입력 :	int _p1, 바꾸려는 원소의 위치 1
			int _p2, 바꾸려는 원소의 위치 2
			int _arr, 원소를 바꿀 배열(힙의 몸체)

	수행 : 주어진 배열의 주어진 위치의 두 원소의 값이 바뀐다.
*/

void swap(int _p1, int _p2, int* _arr) {
	int place1 = _p1;
	int place2 = _p2;
	int* array = _arr;

	int empty = array[place1];
	*(array + place1) = place2;
	*(array + place2) = empty;
}


/*
	---- min_hPush, MAX_hPush ----
	입력 : _v, push할 원소

	수행 : 힙의 몸체에 매개변수로 건네진 값을 넣는다.
	이떄 힙의 규칙에 맞도록 원소들의 위치가 보정된다.

	값을 넣는 방법 : init address는 size(가장 끝 원소의 뒤 원소), 그리고 해당 원소를 기준으로 하여 
	힙의 조건을 만족하지 않는경우, 만족할때까지 swap함
*/

void min_hPush(int _v) {
	int init_address = min_heap[0];
	int value = _v;
	
	for (int address = init_address; address > 0; address /= 2) {
		if (min_heap[address] > min_heap[address / 2]) break;
		swap(address, address / 2, min_heap);
	}
	
	min_heap[0]++;
}

void MAX_hPush(int _v) {
	int init_address = MAX_heap[0];
	int value = _v;

	for (int address = init_address; address > 0; address /= 2) {
		if (MAX_heap[address] > MAX_heap[address / 2]) break;
		swap(address, address / 2, MAX_heap);
	}

	MAX_heap[0]++;
}

/*
	---- push ----
	입력 : _v, push할 원소

	수행 : 이중 Priority Queue에 push하는 함수. 최소힙과 최대힙에 push하는 연산을 실행함.
*/
void push(int _v) {
	int value = _v;
	min_hPush(value);
	MAX_hPush(value);
}


void test_function() {
	int size = min_heap[0];
	int pivot = 1, cnt = 0;
	for (int i = 1; i <= size; i++) {
		printf("%d  ", min_heap[i]);

		if (cnt++ >= pivot) {
			puts("");
			cnt = 0;
			pivot *= 2;
		}
	}
}

int main() {
	min_heap[0] = 1;
	MAX_heap[0] = 1;
	for (int i = 0; i <= 5; i++) {
		int index;
		scanf("%d", &index);
		min_hPush(index);

	}
	test_function();
}


