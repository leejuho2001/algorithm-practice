#define _CRT_SECURE_NO_WARNINGS
/*
	---- 10942_팰린드롬 ----
	메모이제이션을 활용하여 풀이함.
	DT[2002][2002] 를 구성하여 다음과 같은 내용으로 기록.
	1	: 1번 유형 팰린드롬(팰린드롬을 구성하는 모든 수가 같은 팰린드롬)
	2	: 2번 유형 팰린드롬(팰린드롬을 구성하는 수의 종류가 2 가지 이상인 팰린드롬)
	0	: 아직 탐색하지 않음
	-1	: 팰린드롬이 아님.

	팰린드롬 규칙
	: 팰린드롬 조건 : 
	구간 [s, e]를 따질 때, [s+1, e-1] 구간이 팰린드롬이며, arr[s] 와 arr[e]가 같으면 팰린드롬.
	
	1번 유형 팰린드롬 조건 : 
	1. 팰린드롬일것, 
	2. [s+1, e-1] 구간이 1번 유형 팰린드롬일것 
	3. arr[s] == arr[s+1]일것.

	2번 유형 팰린드롬 조건 :	
		기본 팰린드롬 조건을 만족한다는 것을 전제로
		1. [s+1, e-1] 구간이 1번 유형 팰린드롬일 경우, arr[s] != arr[s+1]일것
		2. [s+1, e-1]구간이 2번 유형 팰린드롬일 경우 추가 조건 없음.

	1번 유형 팰린드롬의 성질
	-> [s, e]의 부분집합에 해당하는 구간은 모두 팰린드롬에 해당함.

	팰린드롬이 아닐경우
	: [s-n, e+n] (s-n >= 0 && e+n<= N-1) (N은 수열의 길이) 는 모두 팰린드롬이 아님.
	이를 이용해서 DT를 채워가며 재귀를 이용한 탐색.

	-> 추측 : 별 다른 조건 없는 메모이제이션이 없을 경우 시간초과일 것이다.
	시간초과가 나지않음. 제대로 n^2이 되지 않는 듯함.
	예외가 존재할것으로 보이나, 확실치 않음.
	*/

#include<stdio.h>

int n;
int DT[2002][2002];
int arr[2002];

int isPalindrome(int s, int e) {
	if (DT[s][e] != 0) return DT[s][e];

	if (s == e) return DT[s][e] = 1;
	if (e == s + 1) {
		if (arr[s] == arr[e]) return DT[s][e] = true;
		else {
			return DT[s][e] = -1;
		}
	}

	bool condition1 = arr[s] == arr[e];
	bool condition2 = isPalindrome(s + 1, e - 1) > 0;

	// 1번 조건

	if (condition1 && condition2) {
		return DT[s][e] = 1;
	}
	else {
		return DT[s][e] = -1;
	}

	// 2번 조건
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", arr + i);

	int m; scanf("%d", &m);
	int s, e, res;
	for (int _ = 0; _ < m; _++) {
		scanf("%d %d", &s, &e);
		res = isPalindrome(s-1, e-1);
		if (res > 0) {
			puts("1");
		}
		else {
			puts("0");
		}
	}
}

/*
#include<stdio.h>

int n;
int DT[2002][2002];
int arr[2002];

int isPalindrome(int s, int e) {
	if (DT[s][e] != 0) return DT[s][e];

	if (s == e) return DT[s][e] = 1;
	if (e == s + 1) {
		if (arr[s] == arr[e]) return DT[s][e] = 1;
		else { 
			extendNotPalindrome(s, e);
			return DT[s][e] = -1; 
		}
	}

	bool condition1 = arr[s] == arr[e];
	int  condition2 = isPalindrome(s + 1, e - 1);
	bool condition3 = arr[s] == arr[s + 1];

	// 1번 조건

	if (condition1 && condition2 == 1 && condition3) {
		return DT[s][e] = 1;
	}

	// 2번 조건
}

void extendNotPalindrome(int s, int e) {
	int w = 1;
	if (s == 0 || e == n - 1) return;
	
	if (DT[s - w][e + w] == 0) {
		while (s - w >= 0 && e + w < n) DT[s - w][e + w] = -1;
	}
	return;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", arr + i);
}
*/
// 시도 2. 추가 조건을 붙이는 방법이었으나 위의 시도가 AC를 맞아버려 구현을 중단함.