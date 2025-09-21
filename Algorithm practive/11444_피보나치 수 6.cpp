#define _CRT_SECURE_NO_WARNINGS
/*
---- 피보나치 수 6 ----

[[ a(n + 1)       a(n) ]    @   [[ 1  1 ]  =   [[ a(n)+a(n+1)     a(n+1)]   =    [[ a(n+2) a(n+1) ]
 [ a(n)       a(n - 1) ]]        [ 1  0 ]]      [  a(n) + a(n-1)    a(n)]]        [ a(n+1)   a(n) ]]

	::: 행렬곱을 이용하여 표현할 수 있다. 
	기본 연산 행렬 [[1 1]  :: 을 P라고 두었을때, [[ a(2)  a(1) ]   @  P^n 의 형태로 표현 가능
					[1 1]]						  [ a(1)  a(0) ]] 

	여기서, P^(n+m) = P^n * P^m 으로 정리되는 점을 이용하여,
	분할정복의 형태로 곱셈을 표현 가능.

	--> p(2n) = p(n)^2 or P(2n + 1) = p(n)^2 * P  의 형태로 표현하여 계산
	따라서, n(logn) 의 시간 복잡도를 가짐.
*/

#include<stdio.h>

typedef struct _2_2matrix {
	long long int x_1;  long long int  x_2;
	long long int y_1;  long long int  y_2;
}mat_2x2;

mat_2x2 base = { 1, 1, 1, 0 };

mat_2x2 matmul(mat_2x2 a, mat_2x2 b) {
	mat_2x2 result;
	
	result.x_1 = (a.x_1 * b.x_1 + a.x_2 * b.y_1) % 1000000007;
	result.x_2 = (a.x_1 * b.x_2 + a.x_2 * b.y_2) % 1000000007;
	result.y_1 = (a.y_1 * b.x_1 + a.y_2 * b.y_1) % 1000000007;
	result.y_2 = (a.y_1 * b.x_2 + a.y_2 * b.y_2) % 1000000007;

	return result;
}

mat_2x2 mat_pow(mat_2x2 targ, int power) {
	mat_2x2 base = { 1, 0, 0, 1 };
	
	for (int i = 0; i < power; i++)
		base = matmul(base, targ);
	
	return base;
}

mat_2x2 mat_pow2(mat_2x2 targ) {
	return mat_pow(targ, 2);
}

mat_2x2 fibb(long long int n) {


	if (n == 1) return { 1, 1, 1, 0 };

	mat_2x2 before_step = fibb(n / 2);

	if (n % 2 == 1) {
		mat_2x2 powered = mat_pow2(before_step);
		return matmul(powered, base);
	}
	
	else {
		return mat_pow2(before_step);
	}
}

int main() {
	long long int n; scanf("%lld", &n);

	mat_2x2 fib = fibb(n);
	printf("%lld", fib.x_2);
}




