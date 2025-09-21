#define _CRT_SECURE_NO_WARNINGS
#define epsilon 1e-5
/*
	---- 2166_다각형 ----

	핵심 문제는 내부인가? 외부인가를 구분하는 것.

	하나의 점을 가지고 한 바퀴를 돌린다고 가정하자.
	그럴 경우 각 변은 각자의 방향을 가지게 될 것이다.

	그리고 하나의 점 + 하나의 변으로 이루어진 삼각형을 반시계방향으로
	방향을 주었을 때, 해당 변이 가질 방향이
	맨 처음 한 바퀴를 돌릴때의 방향과 반대라면 외부,
	방향이 같다면 내부에 해당한다.

	따라서 외부에 해당하는 넓이를 모두 빼고, 내부에 해당하는 넓이를 모두 더해주면 답이 나오게 된다.

	1. y축 값이 가장 큰 점을 기준으로 원을 돌려 방향을 정해둔다.
	2. 해당 점과 삼각형을 이룰 수 있는 변들에 대해 방향을 정하고, 해당 방향에 따라서 더하거나, 빼는 여부를 정한다.

	해당 알고리즘은 정점 탐색을 반시계 방향으로 진행한다는 것을 전제로 한다.
	만약 입력받은 정점의 탐색이 시계 방향으로 진행 될 경우, 방향을 반대로 하여 탐색한다.
	방향 :: 가중치에 -1을 곱해줌. (벡터의 반대 개념과 같음)

	어떻게 방향을 알 수 있는가?
	a->b->c의 외적과, b->c->d의 외적을 비교했을 때, 부호가 반대일 경우
	방향이 반대임을 알 수 있다. 따라서 세 점에 대해 외적을 구하는 것이 주요 
	*/


/*
#include<stdio.h>
#include<math.h>

typedef struct _coord {
	long long int x;
	long long int y;
}crd;

typedef struct _vector {
	long long int x;
	long long int y;
}vector;

int n;
crd coords[10005];
int currentdir = 0;

long double triangle(crd a, crd b, crd c);
void setVector(vector* v, crd s, crd e);
long double norm(vector v);
long double dotP(vector a, vector b);
void input();

long long int detZ(vector A, vector B) {
	return (long long int)A.x * B.y - B.x * A.y;
}

long long int getDir(crd a, crd b, crd c) {
	vector vectorA = {};
	vector vectorB = {};
	setVector(&vectorA, a, b);
	setVector(&vectorB, b, c);

	long long int det = detZ(vectorA, vectorB);
	if (det > 0) { currentdir = 1;  return 1; }
	else if (det == 0) return currentdir;
	else { currentdir = -1; return -1; }
}

long double triangle(crd a, crd b, crd c) {
	vector vectorA = {};
	vector vectorB = {};
	vector vectorC = {};
	setVector(&vectorA, a, b);
	setVector(&vectorB, b, c);
	setVector(&vectorC, a, c);
	long double normA = norm(vectorA);
	long double normB = norm(vectorB);
	long double normC = norm(vectorC);
	//printf("%lf %lf %lf\n", normA, normB, normC);
	long double normS = (normA + normB + normC) / 2;

	return (long double)sqrt(normS * (normS - normA) * (normS - normB) * (normS - normC));
}

void setVector(vector* v, crd s, crd e) {
	v->x = e.x - s.x;
	v->y = e.y - s.y;
}

long double norm(vector v) {
	long long int sqdist = (long long int) v.x * v.x + v.y * v.y;
	return (long double)sqrt(sqdist);
}

long double dotP(vector a, vector b) {
	long long int dotp = (long long int )a.x * b.x + a.y * b.y;
	return (long double)dotp;
}


void input() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld", &coords[i].x, &coords[i].y);
	}
}

long double polygon() {
	long double result = 0;
	int a, b, c;
	for (int i = 1; i < n - 1; i++) {
		a = 0, b = (i) % n,  c = (i + 1) % n;
		result += (long double)getDir(coords[a], coords[b], coords[c]) * triangle(coords[a], coords[b], coords[c]);
		
	}

	if (result < 0) return -1 * result;
	else return result;
}


int main() {
	input();

	printf("%.1lf\n", round(polygon() * 10) / 10);
}
*/

#include<stdio.h>
#include<math.h>

typedef struct _coord {
	double x;
	double y;
}crd;

crd coords[10005];

int main() {
	double res = 0;
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		coords[i] = { x, y };
	}

	for (int i = 0; i < n ; i++) {
		int b = i, f = (i + 1) % n;

		res += coords[b].x * coords[f].y;
		res -= coords[b].y * coords[f].x;
	}
	res /= (double)2;
	if (res < 0) res *= (double) - 1;
	printf("%.1lf\n", (double)round((res * 10)) / 10);
}

// 방법 2. 신발끈 공식 사용