#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>			// 메모리 누수를 확인하기 위해 CRT 디버그 함수 사용

#define MAXSTRLEN	16

//------------------------------------------------------------
// Week5_exer1
// Ver3: dummy head 노드 이용
//------------------------------------------------------------

// 단순 연결 리스트의 노드 구조를 구조체로 정의
typedef struct _LISTNODE_ {
	char data[MAXSTRLEN];
	struct _LISTNODE_* next;
} LISTNODE;

// 리스트의 시작을 나타내는 head 노드를 구조체로 정의
typedef struct _LINKEDLIST_ {
	LISTNODE* head;
	int numOfData;
} LINKEDLIST;

/*
 * 연결 리스트 초기화, dummy head 노드 메모리 할당
 */
void InitList(LINKEDLIST* pList)
{
	pList->head = (LISTNODE*)calloc(1, sizeof(LISTNODE)); //메모리 동적 할당
	//pList의 head 인자가 리스트의 시작을 가리킴
	pList->head->next = NULL; //초기값으로 head가 가리키는 주소값은 null로 설정
	pList->numOfData = 0;
}

/*
 * 연결 리스트 메모리 해제
 */
void FreeList(LINKEDLIST* pList)
{
	LISTNODE* pre = pList->head; //현재 head가 가리키고 있는 다음 노드 값을 head에 복사
	LISTNODE* cur = pList->head->next; //head 복사된 값을 다음 노드 값으로 가리킴

	while (cur != NULL)
	{
		pre = cur;
		cur = cur->next;

		free(pre); //해제하고자 하는 노드 해제
		pre = NULL;
	}
	free(pList->head); // head 메모리 해제
	pList->head = NULL;
}

/*
 * 리스트의 맨 앞(head노드가 가리키는 첫번째 노드)에 새로운 노드 추가
 */
void InsertFirst(LINKEDLIST* pList, char* x)
{
	LISTNODE* newNode = NULL;

	newNode = (LISTNODE*)calloc(1, sizeof(LISTNODE)); //newNode 메모리 동적 할당
	strcpy_s(newNode->data, strlen(x)+1, x); 
	newNode->next = NULL;

	newNode->next = pList->head->next; //head를 통해 newNode에 값 대입
	pList->head->next = newNode; 
	pList->numOfData += 1;			// 데이터 수 증가
}

/*
 * 리스트의 마지막에 새로운 노드 추가
 */
void InsertLast(LINKEDLIST* pList, char* x)
{
	LISTNODE* pre = NULL;
	LISTNODE* cur = NULL;
	LISTNODE* newNode = NULL;

	newNode = (LISTNODE*)calloc(1, sizeof(LISTNODE));
	strcpy_s(newNode->data, strlen(x) + 1, x);
	newNode->next = NULL;

	pre = pList->head; 
	cur = pList->head->next;		// head는 초기화 과정에서 dummy로 만들어주었으므로, head->next 부터 순회
	while (cur != NULL) // 값을 리스트 한 칸 씩 뒤로 미는 과정
	{
		pre = cur; 
		cur = cur->next;
	}
	//newNode->next = NULL;			// NULL임
	newNode->next = pre->next;		// NULL 임
	pre->next = newNode;
	pList->numOfData += 1;			// 데이터 수 증가
}

/*
 * data x를 가진 노드 리스트에서 찾아서 주소 반환
 */
LISTNODE* SearchNode(LINKEDLIST* pList, char* x)
{
	LISTNODE* cur = NULL;
	cur = pList->head->next; //현재 노드의 다음 노드 가리킴

	while (cur != NULL)
	{
		if (strncmp(cur->data, x, MAXSTRLEN) == 0) //str 비교해서 같으면 cur return
		{
			return cur;
		}
		cur = cur->next; 
	}

	return cur;
}

/*
 * targer 노드를 리스트에서 삭제
 */
void DeleteNode(LINKEDLIST* pList, LISTNODE* target)
{
	LISTNODE* pre = NULL;
	LISTNODE* cur = NULL;

	if (pList->head->next == NULL || target == NULL)
	{
		fprintf(stderr, "Error, null pointer\n");
		return;
	}
	else
	{
		pre = pList->head;
		cur = pList->head->next; //삭제하고자 하는 노드 다음 노드의 주소를 삭제하고자 하는 노드의 앞 노드 link로 전달하는 과정

		while (cur != NULL)
		{
			if (cur == target)
			{
				pre->next = cur->next; 
				free(cur);
				cur = NULL;
				break;
			}
			pre = cur; //현재 cur이 가리키고 있는 노드가 샂게할 노드가 아닐 때 다음 노드로 계속 밀기
			cur = cur->next;
		}
	}
	pList->numOfData -= 1;
}

/*
 * list의 정보를 출력
 */
void PrintList(LINKEDLIST* pList)
{
	LISTNODE* cur = NULL;

	cur = pList->head->next;
	printf("L = (");
	while (cur != NULL)
	{
		printf("%s", cur->data);
		cur = cur->next;
		if (cur != NULL)
		{
			printf(", ");
		}
	}
	printf(")\n"); 
}

int main()
{
	LINKEDLIST list;
	LISTNODE* find = NULL;

	InitList(&list); //빈 리스트 생성

	InsertFirst(&list, "a"); //리스트의 맨 처음에 a 삽입
	InsertFirst(&list, "b"); //리스트의 맨 처음에 b 삽입
	InsertFirst(&list, "c"); //리스트의 맨 처음에 c 삽입
	InsertFirst(&list, "d"); //리스트의 맨 처음에 d 삽입

	PrintList(&list); //리스트 출력

	InsertLast(&list, "e"); //리스트의 맨 마지막에 e 삽입
	InsertLast(&list, "f"); //리스트의 맨 마지막에 f 삽입
	InsertLast(&list, "g"); //리스트의 맨 마지막에 g 삽입
	InsertLast(&list, "h"); //리스트의 맨 마지막에 h 삽입

	PrintList(&list); //리스트 출력

	find = SearchNode(&list, "h"); //리스트 중 h 탐색
	if (find == NULL) 
		printf("찾는 데이터가 없습니다.\n"); 
	else printf("[%s]를 찾았습니다.\n", find->data);

	DeleteNode(&list, find); //탐색한 노드를 리스트에서 삭제
	PrintList(&list); //리스트 출력

	find = SearchNode(&list, "e"); //리스트 중 e 탐색
	if (find == NULL) printf("찾는 데이터가 없습니다.\n");
	else printf("[%s]를 찾았습니다.\n", find->data);

	DeleteNode(&list, find);
	PrintList(&list);

	FreeList(&list);

	return 0;
}
