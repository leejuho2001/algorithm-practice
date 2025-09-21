#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1967_트리의 지름 ----

	아이디어 : 분할정복 사용.
	하나의 트리에 대해서 세가지 결과를 얻을 수 있다.
	1. 왼쪽 subtree에서 head까지의 거리의 최대
	2. 오른쪽 subtree에서 head까지의 거리의 최대
	3. 왼쪽 subtree에서 오른쪽 subtree까지의 거리의 최대.

	3번은 해당 트리의 지름이 된다.
	상위 트리에 값을 전달하기 위해선 subtree에서의 거리를 반환하므로, 1과 2 중 더욱 큰 값을 반환한다.


	입력을 순서대로 진행하면 트리가 완성된다는 보장이 없음.
	이를 해결하기 위해 큐를 사용. 트리에서 값을 찾지 못했을 경우엔 front값을 다시 push해줌.
	그리고 자식노드 생성에 성공한 경우 정보를 pop함. 
	*/

#include<stdio.h>
#include<stdlib.h>
#include<queue>
using namespace std;

// 트리 완성 보장을 위한 큐
// 여기에 저장된 모든 데이터가 pop되기 전까지는 계속해서 진행됨.
queue<int>parent;
queue<int>child;
queue<int>weight;

void pushAll(int _parent, int _child, int _weight) {
	parent.push(_parent);
	child.push(_child);
	weight.push(_weight);
}

void popAll() {
	parent.pop();
	child.pop();
	weight.pop();
}

void replaceQ() {
	parent.push(parent.front());
	child.push(child.front());
	weight.push(weight.front());

	popAll();
}



int MAX = 0;

struct _node;
struct _listNode;

typedef struct _node {
	int childNum;
	int key;
	int weightToParent;
	_listNode* childList;
}node;

node origin = { 191919, 0, NULL };

typedef struct _listNode {
	_node* childNode;
	_listNode* next;
}listNode;

node* createNode(int _key, int _weight) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->childNum = 0;
	newNode->key = _key;
	newNode->weightToParent = _weight;
	newNode->childList = NULL;

	return newNode;
}

/*
	---- addChild ----
	입력 : 부모노드와 자식노드.

	행동 : 자식노드를 부모노드의 자식 리스트에 추가함.
	자식노드를 listNode로 감싸준 뒤,
	해당 listNode를 parentNode의 childList에 추가.
	추가가 완료되었을 경우, 부모노드의 parentNode의 수를 나타내는 childNum 1 증가

*/

void addChild(node* _parentNode, node* _childNode) {
	listNode* newListNode = (listNode*)malloc(sizeof(listNode));
	newListNode->childNode = _childNode;
	newListNode->next = NULL;

	listNode* visitor = _parentNode->childList;
	if (visitor == NULL) _parentNode->childList = newListNode;
	else {
		while (visitor->next != NULL) visitor = visitor->next;
		visitor->next = newListNode;
	}
	_parentNode->childNum++;
}

/*
	searchNode 종료조건.
	1. 해당 Node가 child를 가지지 않는경우 ( childnum == 0 )
	2. 해당 Node가 
	3. 한 서브트리에서 search에 성공한경우 ( result != NULL)
	4. key값이 요구된 key값과 같은 경우.
*/

node* searchNode(int _key, node* _node) {
	int key = _key;
	if (_node->key == key) return _node;
	else if (_node->childNum == 0) return NULL;

	listNode* list = _node->childList;
	while (1) {
		node* result = searchNode(key, list->childNode);
		if (result != NULL) return result;
		// 자식 트리에서 발견한 경우 그 발견한걸 위로 올려보냄.
		list = list->next;
		if (list == NULL) break;
	}

	return NULL;
	// 찾지못한경우 NULL을 리턴.
}


/*
	---- add_leaf ----
	입력 : 부모노드의 키, 추가할 키와 간선의 weight + 트리의 루트노드

	부모노드의 트리를 찾은 뒤
*/
void add_leaf(int _parentKey, int _key, int _weight, node *_root) {
	int parentKey = _parentKey;
	int key = _key;
	int weight = _weight;
	node* root = _root;

	node* newNode = createNode(key, weight);
	node* currentNode = searchNode(parentKey, root);
	if (currentNode == NULL) {
		//printf("error :: node with key %d does not exist", _parentKey);
		replaceQ();
		return;
	}

	addChild(currentNode, newNode);
	popAll();
	return;
}


int MAX_treeDiag(node* _head) {
	int first = 0;
	int second = 0;
	if (_head->childNum == 0) return _head->weightToParent;

	listNode* visitor = _head->childList;
	while (visitor!= NULL) {
		int res = MAX_treeDiag(visitor->childNode);
		if (res > second) second = res;
		if (res > first) {
			int temp = first;
			first = second;
			second = temp;
		}// swap
		visitor = visitor->next;
	}
	if (first + second > MAX) MAX = first + second;
	// 서브트리의 최댓값이 MAX보다 크다면 변경.

	return first+_head->weightToParent;
}

void input1(int n) {

	for (int i = 0; i < n-1; i++) {
		int parent, child, weight;
		scanf("%d %d %d", &parent, &child, &weight);
		pushAll(parent, child, weight);
	}
}
/*
void input2(int n) {
	for (int i = 0; i < n; i++) {
		int parent, child, weight;
		scanf("%d", &parent);

		while (1) {
			scanf("%d", &child);
			if (child == -1) break;
			scanf("%d", &weight);

			pushAll(parent, child, weight);
		}
	}
}*/

// 1167번 문제 풀이를 위해 만들어졌으나, 방향이 없는 트리였기때문에 보류.

/*
	---- buildTree ----
	입력 : 루트노드
	행동 : 큐에 저장되어있는 모든 간선 데이터들을 사용하여 트리를 build함.

*/

void buildTree(node* root) {
	while (!parent.empty()) {
		int parent_ = parent.front();
		int child_ = child.front();
		int weight_ = weight.front();

		add_leaf(parent_, child_, weight_, root);
	}
}

int main() {
	int n;
	node* root = (node*)malloc(sizeof(node));
	root->key = 1;
	root->weightToParent = 0;
	root->childList = NULL;
	root->childNum = 0;

	scanf("%d", &n);
	input1(n);
	buildTree(root);

	MAX_treeDiag(root);

	printf("%d", MAX);

}