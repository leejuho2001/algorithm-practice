#define _CRT_SECURE_NO_WARNINGS
/*
    ---- 11053_���� �� �����ϴ� �κ� ���� ----

    :: ������ : ������ ������ 1000���� 1000000���� �þ���.
    ����, ������ �迭�� ���� DP�� ������ �� ����.

    ->segment tree�� ����Ѵ�.
    �ش� �κ��� A�� �θ�
    �ش� segment tree :: 1~A ������ ���� �̷���� ���� �� ���� �� �����ϴ� �κ� ������ ���� ����.
    ����, 1~A ������ ���� �� ���� �� ������ ���̸� ���ϴ� �� log A ��ŭ�� �ð��� �ɸ���.
    ����, ������ Ǯ���ϴµ� NlogN�� �ð����⵵�� ������ �ȴ�.

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
