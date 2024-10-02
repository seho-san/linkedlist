#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>			// �޸� ������ Ȯ���ϱ� ���� CRT ����� �Լ� ���

#define MAXSTRLEN	16

//------------------------------------------------------------
// Week5_exer1
// Ver3: dummy head ��� �̿�
//------------------------------------------------------------

// �ܼ� ���� ����Ʈ�� ��� ������ ����ü�� ����
typedef struct _LISTNODE_ {
	char data[MAXSTRLEN];
	struct _LISTNODE_* next;
} LISTNODE;

// ����Ʈ�� ������ ��Ÿ���� head ��带 ����ü�� ����
typedef struct _LINKEDLIST_ {
	LISTNODE* head;
	int numOfData;
} LINKEDLIST;

/*
 * ���� ����Ʈ �ʱ�ȭ, dummy head ��� �޸� �Ҵ�
 */
void InitList(LINKEDLIST* pList)
{
	pList->head = (LISTNODE*)calloc(1, sizeof(LISTNODE)); //�޸� ���� �Ҵ�
	//pList�� head ���ڰ� ����Ʈ�� ������ ����Ŵ
	pList->head->next = NULL; //�ʱⰪ���� head�� ����Ű�� �ּҰ��� null�� ����
	pList->numOfData = 0;
}

/*
 * ���� ����Ʈ �޸� ����
 */
void FreeList(LINKEDLIST* pList)
{
	LISTNODE* pre = pList->head; //���� head�� ����Ű�� �ִ� ���� ��� ���� head�� ����
	LISTNODE* cur = pList->head->next; //head ����� ���� ���� ��� ������ ����Ŵ

	while (cur != NULL)
	{
		pre = cur;
		cur = cur->next;

		free(pre); //�����ϰ��� �ϴ� ��� ����
		pre = NULL;
	}
	free(pList->head); // head �޸� ����
	pList->head = NULL;
}

/*
 * ����Ʈ�� �� ��(head��尡 ����Ű�� ù��° ���)�� ���ο� ��� �߰�
 */
void InsertFirst(LINKEDLIST* pList, char* x)
{
	LISTNODE* newNode = NULL;

	newNode = (LISTNODE*)calloc(1, sizeof(LISTNODE)); //newNode �޸� ���� �Ҵ�
	strcpy_s(newNode->data, strlen(x)+1, x); 
	newNode->next = NULL;

	newNode->next = pList->head->next; //head�� ���� newNode�� �� ����
	pList->head->next = newNode; 
	pList->numOfData += 1;			// ������ �� ����
}

/*
 * ����Ʈ�� �������� ���ο� ��� �߰�
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
	cur = pList->head->next;		// head�� �ʱ�ȭ �������� dummy�� ������־����Ƿ�, head->next ���� ��ȸ
	while (cur != NULL) // ���� ����Ʈ �� ĭ �� �ڷ� �̴� ����
	{
		pre = cur; 
		cur = cur->next;
	}
	//newNode->next = NULL;			// NULL��
	newNode->next = pre->next;		// NULL ��
	pre->next = newNode;
	pList->numOfData += 1;			// ������ �� ����
}

/*
 * data x�� ���� ��� ����Ʈ���� ã�Ƽ� �ּ� ��ȯ
 */
LISTNODE* SearchNode(LINKEDLIST* pList, char* x)
{
	LISTNODE* cur = NULL;
	cur = pList->head->next; //���� ����� ���� ��� ����Ŵ

	while (cur != NULL)
	{
		if (strncmp(cur->data, x, MAXSTRLEN) == 0) //str ���ؼ� ������ cur return
		{
			return cur;
		}
		cur = cur->next; 
	}

	return cur;
}

/*
 * targer ��带 ����Ʈ���� ����
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
		cur = pList->head->next; //�����ϰ��� �ϴ� ��� ���� ����� �ּҸ� �����ϰ��� �ϴ� ����� �� ��� link�� �����ϴ� ����

		while (cur != NULL)
		{
			if (cur == target)
			{
				pre->next = cur->next; 
				free(cur);
				cur = NULL;
				break;
			}
			pre = cur; //���� cur�� ����Ű�� �ִ� ��尡 ������ ��尡 �ƴ� �� ���� ���� ��� �б�
			cur = cur->next;
		}
	}
	pList->numOfData -= 1;
}

/*
 * list�� ������ ���
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

	InitList(&list); //�� ����Ʈ ����

	InsertFirst(&list, "a"); //����Ʈ�� �� ó���� a ����
	InsertFirst(&list, "b"); //����Ʈ�� �� ó���� b ����
	InsertFirst(&list, "c"); //����Ʈ�� �� ó���� c ����
	InsertFirst(&list, "d"); //����Ʈ�� �� ó���� d ����

	PrintList(&list); //����Ʈ ���

	InsertLast(&list, "e"); //����Ʈ�� �� �������� e ����
	InsertLast(&list, "f"); //����Ʈ�� �� �������� f ����
	InsertLast(&list, "g"); //����Ʈ�� �� �������� g ����
	InsertLast(&list, "h"); //����Ʈ�� �� �������� h ����

	PrintList(&list); //����Ʈ ���

	find = SearchNode(&list, "h"); //����Ʈ �� h Ž��
	if (find == NULL) 
		printf("ã�� �����Ͱ� �����ϴ�.\n"); 
	else printf("[%s]�� ã�ҽ��ϴ�.\n", find->data);

	DeleteNode(&list, find); //Ž���� ��带 ����Ʈ���� ����
	PrintList(&list); //����Ʈ ���

	find = SearchNode(&list, "e"); //����Ʈ �� e Ž��
	if (find == NULL) printf("ã�� �����Ͱ� �����ϴ�.\n");
	else printf("[%s]�� ã�ҽ��ϴ�.\n", find->data);

	DeleteNode(&list, find);
	PrintList(&list);

	FreeList(&list);

	return 0;
}
