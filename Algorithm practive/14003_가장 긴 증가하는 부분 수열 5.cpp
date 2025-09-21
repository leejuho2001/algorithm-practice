#define _CRT_SECURE_NO_WARNINGS
/*
    ---- 11053_가장 긴 증가하는 부분 수열 5 ----

    :: 변경점 : 숫자의 범위가 -10^9 ~ 10^9로 늘었다.
    세그먼트 트리가 숫자의 범위가 작음을 이용한 풀이였으나, 
    숫자의 범위가 너무 커져 세그먼트 트리도 활용할 수 없게 되었다.

    -> 다른 DP 풀이 방법이 필요하다.

    idea : 현재 DP 방식은 현재까지 가장 긴 수열을 기반으로 한다.
    따라서 뒷 숫자는 고려하지 않는다.

    현재 번호가 길이가 n인 수열의 마지막 수가 되기 위해선, n-1번째 수보다 더 커야한다.
    이 조건 때문에, 길이가 n-1인 수열 중에선 가장 작은 원소를 가진 수열이 유리하다.
    이 점을 이용해 길이가 n인 수열에서 가장 작은 마지막 원소를 저장하는 배열을 만들어 활용하면 된다.
    그렇게 될 경우, 해당 배열은 오름차순으로 정렬된다.
    이를 이용해, 이분탐색을 하여 다음 원소의 값을 찾는다.

    이분탐색은 O(logN)의 복잡도를 가지므로, 최종적으로 O(NlogN)의 시간복잡도를 가진다.

    출력은 어떻게 할 것인가?
    :: 가장 긴 길이가 나왔을 경우, 이 이전 element를 따라갈 수 있도록 해주어야 한다.
    따라서 길이가 n인 수열 중, 마지막 원소가 가장 작은 수열에서 n-1번째 수를 저장하는 
    */
#include<stdio.h>
#include<stack>
using namespace std;
#define end 1000000
#define start 1
stack<int>subseq;

int SLE[1000050]; // smallest last element.
int SLE_add[1000050];
int sequence[1000050];
int before[1000050];
int n;
int MAX;

int biSearch(int s, int e, int value) {
    if (s == e) return s-1;

    int center = (s + e) / 2;
    if (sequence[SLE[center]] >= value) return biSearch(s, center, value);
    else return biSearch(center + 1, e, value);
}

void LIS() {
    for (int i = 1; i <= n; i++) {
        int curr = sequence[i];
        int address = biSearch(start, end, curr);
        //printf("%d - %d\n",curr, address);

        if (SLE[address+1] == 0 ||sequence[SLE[address + 1]] > curr) { 
            SLE[address + 1] = i; 
            before[i] = SLE[address];
            if (address + 1 > MAX) MAX = address + 1;
        }


    }
    int st = SLE[MAX];
    while(before[st] >= 0){
        subseq.push(sequence[st]);
        if (before[st] == 0) break;
        st = before[st];
    } 


    
    printf("%d\n", MAX);

    while (!subseq.empty()) {
        printf("%d ", subseq.top());
        subseq.pop();
    }
}

void initialize() {
    sequence[0] = 1000000050;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", sequence + i);
    initialize();
    LIS();
}

//10 20 30 20 50 70 60 40 80