/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University.
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("----------[정새연] [2023041074]----------\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); 			//node에 메모리 할당
	listNode* p; 													//p는 리스트의 값을 가리키도록
	listNode* previous; 											//p보다 한 단계 이전 값을 가리키게 함
	node->key = key; 												//node에 key 값 저장

	if (h->first == NULL) {											//list에 값이 하나도 없으면
		node->link = NULL; 											//node가 가리키는 값에는 NULL을 넣는다
		h->first = node; 											//첫 번째 값에 node를 넣고 종료한다
		return 0;
	}
	else if(h->first->link == NULL){ 								//리스트의 값이 하나라면
		if (h->first->key > node->key)								//그 하나의 값이 node 값보다 크다면 
		{
			node->link = h->first; 									//node가 가리키는 값에는 h->first를 넣고
			h->first = node; 										//그 한 값의 앞에 node 삽입
		}
		else 														//그 하나의 값이 node 값보다 작거나 같다면
		{
			h->first->link = node; 									//h->first가 가리키는 값에는 node를 넣고
			node->link = NULL; 										//그 한 값의 뒤에 node 삽입
		}
		return 0;
	}
	else if(h->first->key > node->key) 								// 리스트의 첫 번째 값에 node를 삽입해야 한다면
	{
		node->link = h->first; 										//node가 가리키는 값에는 h->first를 넣고
		h->first = node; 											//첫 번째 값에 node를 넣고 종료한다
		return 0;
	}
	else 															//리스트의 두 번째 이상의 값에 node를 삽입해야 한다면
	{
		previous = h->first; 										//previous는 리스트의 첫 번째 값을 가리게한다
		p = h->first->link; 										//p는 리스트의 두 번째 값을 가리키게 한다
		if(previous->key < key && p->key > key) 					//리스트에 값이 두 개 있고 그 사이에 삽입해야 한다면
		{
			previous->link = node; 									//previous가 가리키는 값을 node로 하고
			node->link = p; 										//node는 p를 가리키게 하고 종료한다
			return 0;
		}
		else
		{
			while (p->key <= node->key && p->link != NULL) 			//p의 key 값이 node의 key 값보다 크거나 p가 리스트의 마지막에 도달 할 때 까지 반복한다
			{
				previous = p; 										//previous는 p를 가리키고
				p = p->link; 										//p는 다음 값을 가리킨다
			}
			if (p->link == NULL)									//리스트의 가장 마지막에 도달했다면
			{
				p->link = node; 									//리스트의 마지막 원소가 node를 가리키게 하고
				node->link = NULL; 									//node가 NULL을 가리키게 한다
			}
			else 
			{
				previous->link = node; 								//previous가 가리키는 값을 node로 하고
				node->link = p; 									//node는 p를 가리키게 하고 종료한다
			}
			return 0;
		}
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	int i; 															//i는 for문을 돌리기 위한 변수
	listNode* p ;  													//p는 리스트의 값을 가리키도록
	listNode* node = (listNode*)malloc(sizeof(listNode)); 			//node에 메모리 할당
	node->key = key; 												//node에 key 값 저장

	if (h->first == NULL) 											//list에 값이 하나도 없으면
	{
		node->link = NULL; 											//node가 가리키는 값에는 NULL을 넣는다
		h->first = node; 											//첫 번째 값에 node를 넣고 종료한다
		return 0;
	}
	else 															//그렇지 않으면 아래를 실행한다
	{
		for (i = 0, p = h->first; p->link != NULL; p = p->link)  	//p가 리스트의 첫 번째 값을 가리키게 하고 p가 리스트의 마지막을 가리키게 하는 for문을 돌린다
			i++;  													//i는 리스트의 길이를 나타낸다
		node->link = NULL; 											//node가 가리키는 값에는 NULL을 넣는다
		p->link = node; 											//p가 가리키는 곳에 node 주소를 넣음 => list의 가장 끝에 node를 넣고 종료
		return 0;
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p;
	if (h->first == NULL) 											//리스트가 이미 비어있다면 -1을 리턴한다
	{
		printf("list is already empty !!\n");
		return -1;
	}
	else 															//리스트가 비어있지 않다면
	{
		p = h->first; 												//p에 리스트의 첫 번째 주소 저장
		h->first = p->link; 										//리스트의 첫 번째 값을 리스트의 두 번째 값으로 변경
		free(p); 													//p의 메모리를 free함으로써 원래 리스트의 첫 번째 값의 메모리 해제
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* p;
	listNode* pre; 											//pre는 p의 하나 전을 가리킨다
	if (h->first == NULL) 									//리스트가 이미 비어있다면 -1을 리턴한다
	{
		printf("list is already empty !!\n");
		return -1;
	}
	else if (h->first->link == NULL) 						//리스트의 값이 하나이고
	{
		if (h->first->key == key) 							//그 값이 key와 같다면
		{
			p = h->first; 									//p에 리스트의 첫 번째 값을 저장하고
			h->first = NULL; 								//그 값을 삭제하고
			free(p); 										//원래 있던 값을 메모리 해제 
		}
		else 												//리스트에 그 값이 없다면 -1을 리턴한다
		{
			printf("not in list !!\n");
			return -1;
		}
	}
	else 													//리스트에 값이 두 개 이상이라면
	{
		p = h->first->link; 								//p는 리스트의 두 번째 값을 저장하고
		pre = h->first; 									//pre는 리스트의 첫 번째 값을 저장한다
		if (pre->key == key) 								//리스트의 첫 번째 값이 key와 같다면
		{
			h->first = p; 									//리스트의 첫 번째 값을 p로 바꾸고
			pre->link = NULL; 								//pre는 NULL을 가리키게 한 뒤
			free(pre);	 									//pre를 메모리 해제하고
			return 0; 										//종료한다
		}
		while (p->key != key && p->link != NULL) 			//p의 key 값이 key와 같거나 p가 가장 마지막을 가리킬 때 까지 반복한다 
		{
			pre = p; 										//pre는 p를 가리키고
			p = p->link; 									//p는 다음 값을 가리킨다
		}
		if (p->link == NULL)								//리스트의 가장 마지막에 도달했다면 리스트에 값이 없는 것이다
		{
			printf("not in list !!\n");
			return -1;
		}
		else 												//p는 key와 같은 값을 가진 리스트를 가리키고 있다
		{
			pre->link = p->link; 							//pre 다음이 p 다음을 가리키게 하고
			p->link = NULL; 								//p는 NULL을 가리키게 한 뒤
			free(p); 										//p를 메모리 해제한다
		}
	}
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* p;
	listNode* pre; 											//pre는 p의 하나 전을 가리킨다
	if (h->first == NULL) 									//리스트가 이미 비어있다면 -1을 리턴한다
	{
		printf("list is already empty !!\n");
		return -1;
	}
	else if(h->first->link == NULL) 						//리스트의 값이 하나라면
	{
		p = h->first->link; 								//p가 그 한 값을 가리키게 한다.
		h->first = NULL; 									//리스트를 비우고
		free(p); 											//원래 있던 한 값을 메모리 해제 한다
	}
	else 													//리스트의 값이 두개 이상이라면
	{
		pre = h->first; 									//pre는 리스트의 첫 번째 값을 가리게한다
		p = h->first->link; 								//p는 리스트의 두 번째 값을 가리키게 한다
		while (p->link != NULL) 							//p가 가리키는 값이 없을 때 까지
		{
			pre = p; 										//pre는 p를 가리키고
			p = p->link; 									//p는 다음 단계를 가리킨다
		}
		//반복문을 나왔으므로 p는 가장 마지막 원소를 가리킴
		pre->link = NULL; 									//pre가 NULL을 가리키게 함으로써 마지막 원소를 삭제하고ㅓ
		free(p); 											//원래 마지막이었던 메모리를 해제한다

	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* pre; 											//p 이전을 가리킴
	listNode* p; 											//리스트의 값을 가리킴
	listNode* next; 										//p 다음을 가리킴
	if (h->first == NULL || h->first->link == NULL ) 		// 리스트가 비어있거나 리스트의 원소가 하나라면 그냥 종료
		return 0;
	else if (h->first->link->link == NULL) 					// 리스트의 원소가 두 개라면 그 둘을 바꿈
	{
		p = h->first->link; 								//p는 리스트의 두 번째 원소
		pre = h->first; 									//pre는 리스트의 첫 번째 원소
		h->first = p; 										//첫 번째 원소를 p로 바꾸고
		p->link = pre; 										//p다음 원소는 pre로 한다
		pre->link = NULL; 									//pre 다음은 NULL이다
		return 0;
	}
	else 													//리스트의 원소가 세 개 이상이라면
	{
		pre = h->first; 									//pre는 첫 번째 원소를 가리키고
		p = pre->link; 										//p는 pre 다음 원소를
		next = p->link; 									//next는 p 다음 원소를 가리킨다
		pre->link = NULL; 									//리스트의 첫 번째 원소가 NULL을 가리키게 하고
		while (next->link != NULL) 							//next가 리스트의 마지막이면 반복문을 종료한다
		{
			p->link = pre; 									//p 다음은 pre를 가리키게 하고
			pre = p; 										//pre는 다음을 가리키고
			p = next; 										//p도 다음을 가리킨다
			next = next->link; 								//next도 다음을 가리킨다
		}
		p->link = pre; 										//p 다음은 pre를 가리키게 하고
		h->first = next; 									//리스트의 첫 번째 원소는 next가 되고
		next->link = p; 									//next 다음은 p가 된다
		return 0;
	}
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

