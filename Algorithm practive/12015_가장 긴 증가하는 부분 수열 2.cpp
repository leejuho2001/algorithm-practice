#define _CRT_SECURE_NO_WARNINGS
/*
    ---- 11053_가장 긴 증가하는 부분 수열 ----

    :: 변경점 : 숫자의 개수가 1000에서 1000000개로 늘었다.
    따라서, 이차원 배열을 통해 DP를 시행할 수 없다.

    ->segment tree를 사용한다.
    해당 부분을 A라 두면
    해당 segment tree :: 1~A 까지의 수로 이루어진 수들 중 가장 긴 증가하는 부분 수열의 길이 저장.
    따라서, 1~A 까지의 값들 중 가장 긴 수열의 길이를 구하는 데 log A 만큼의 시간이 걸린다.
    따라서, 문제를 풀이하는데 NlogN의 시간복잡도를 가지게 된다.

*/

#include<stdio.h>

int n;
int numbers[1000050];
int seq_len[2100000];

void fix_segTree(int s, int e, int val, int add, int index) {
    int center = (s + e) / 2;
    if (seq_len[index] < val) seq_len[index] = val;
    if (s == e) return;

    if (add > center) fix_segTree(center + 1, e, val, add, index * 2 + 1);
    else fix_segTree(s, center, val, add, index * 2);
}

int find_maxVal(int s, int e, int add, int index) {
    if (s > add) return -1;
    else if (e <= add) return seq_len[index];
    else if (s == e) return seq_len[index];

    int center = (s + e) / 2;
    int case1 = find_maxVal(s, center, add, index * 2);
    int case2 = find_maxVal(center + 1, e, add, index * 2+1);
    if (case2 == -1) return case1;
    else return case1 > case2 ? case1 : case2;
}

int main() {
    int n; scanf("%d", &n);
    int temp;
    for (int _ = 0; _ < n; _++) {
        scanf("%d", &temp);
        int max = find_maxVal(1, 1000000, temp-1, 1);
        if (max == -1) max = 0;
        //printf("%d\n", max);
        fix_segTree(1, 1000000, max+1, temp, 1);
    }

    int res = find_maxVal(1, 1000000, 1000000, 1);
    printf("%d", res);
}
