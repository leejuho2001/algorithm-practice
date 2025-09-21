#define _CRT_SECURE_NO_WARNINGS

/*
	---- 1967_Ʈ���� ���� ----

	���̵�� : �������� ���.
	�ϳ��� Ʈ���� ���ؼ� ������ ����� ���� �� �ִ�.
	1. ���� subtree���� head������ �Ÿ��� �ִ�
	2. ������ subtree���� head������ �Ÿ��� �ִ�
	3. ���� subtree���� ������ subtree������ �Ÿ��� �ִ�.

	3���� �ش� Ʈ���� ������ �ȴ�.
	���� Ʈ���� ���� �����ϱ� ���ؼ� subtree������ �Ÿ��� ��ȯ�ϹǷ�, 1�� 2 �� ���� ū ���� ��ȯ�Ѵ�.


	�Է��� ������� �����ϸ� Ʈ���� �ϼ��ȴٴ� ������ ����.
	�̸� �ذ��ϱ� ���� ť�� ���. Ʈ������ ���� ã�� ������ ��쿣 front���� �ٽ� push����.
	�׸��� �ڽĳ�� ������ ������ ��� ������ pop��. 
	*/

#include<stdio.h>
#include<stdlib.h>
#include<queue>
using namespace std;

// Ʈ�� �ϼ� ������ ���� ť
// ���⿡ ����� ��� �����Ͱ� pop�Ǳ� �������� ����ؼ� �����.
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
	�Է� : �θ���� �ڽĳ��.

	�ൿ : �ڽĳ�带 �θ����� �ڽ� ����Ʈ�� �߰���.
	�ڽĳ�带 listNode�� ������ ��,
	�ش� listNode�� parentNode�� childList�� �߰�.
	�߰��� �Ϸ�Ǿ��� ���, �θ����� parentNode�� ���� ��Ÿ���� childNum 1 ����

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
	searchNode ��������.
	1. �ش� Node�� child�� ������ �ʴ°�� ( childnum == 0 )
	2. �ش� Node�� 
	3. �� ����Ʈ������ search�� �����Ѱ�� ( result != NULL)
	4. key���� �䱸�� key���� ���� ���.
*/

node* searchNode(int _key, node* _node) {
	int key = _key;
	if (_node->key == key) return _node;
	else if (_node->childNum == 0) return NULL;

	listNode* list = _node->childList;
	while (1) {
		node* result = searchNode(key, list->childNode);
		if (result != NULL) return result;
		// �ڽ� Ʈ������ �߰��� ��� �� �߰��Ѱ� ���� �÷�����.
		list = list->next;
		if (list == NULL) break;
	}

	return NULL;
	// ã�����Ѱ�� NULL�� ����.
}


/*
	---- add_leaf ----
	�Է� : �θ����� Ű, �߰��� Ű�� ������ weight + Ʈ���� ��Ʈ���

	�θ����� Ʈ���� ã�� ��
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
	// ����Ʈ���� �ִ��� MAX���� ũ�ٸ� ����.

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

// 1167�� ���� Ǯ�̸� ���� �����������, ������ ���� Ʈ�����⶧���� ����.

/*
	---- buildTree ----
	�Է� : ��Ʈ���
	�ൿ : ť�� ����Ǿ��ִ� ��� ���� �����͵��� ����Ͽ� Ʈ���� build��.

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