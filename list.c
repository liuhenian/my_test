#include "list.h"

#define RETURN_IF_NULL(node) do { \
	if (node == NULL) { \
		return;	\
	} \
}while (0)

MyLinkedList* myLinkedListCreate()
{
	MyLinkedList *mylist = (MyLinkedList *)malloc(sizeof(struct MyLinkedList));
	mylist->head = NULL;
	mylist->tail = NULL;
	return mylist;
}

int myLinkedListGet(MyLinkedList* obj, int index)
{
	list_node *node;
	int findnode = -1;
	node = obj->head;
	if (obj == NULL || index < 0 || node == NULL){
		return findnode;
	}
	int i;
	for (i = 1 ; i <= index ; i++ )
	{
		node = node->next;
		if(node == NULL){
			return findnode;
		}
	}
	findnode = node->val;
	return findnode;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val)
{
	RETURN_IF_NULL(obj);
	list_node *node = (list_node *)malloc(sizeof(struct list_node));
	RETURN_IF_NULL(node);
	node->prev = NULL;
	node->next = obj->head;
	node->val = val;
	if(obj->head)
	{
		obj->head ->prev = node;
	}
	obj->head = node;
	if (obj->tail == NULL) {
		obj->tail = node;
	}
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val)
{
	RETURN_IF_NULL(obj);
	list_node *node = (list_node *)malloc(sizeof(struct list_node));
	RETURN_IF_NULL(node);
	node->val = val;
	if (obj->tail == NULL) {
		node->prev = NULL;
		node->next = NULL;
		obj->head = node;
		obj->tail = node;
		return;
	}
	node->prev = obj->tail;
	node->prev->next = node;
	node->next = NULL;
	obj->tail = node;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val)
{
	RETURN_IF_NULL(obj);
	list_node *node = obj->head;
	if (index < 0 ) {
		return ;
	}

	if(node == NULL && index > 0)
	{
		return;
	}
	/*在头部插入*/
	if(node == NULL || index == 0)
	{
		myLinkedListAddAtHead(obj, val);
		return;
	}
	/*其他位置插入*/
	int i;
	for(i = 1 ; i <= index ; i++) {
        node = node->next;
        if(node == NULL) {
            break;
        }
	}
	if(node == NULL)
	{
		myLinkedListAddAtTail(obj, val);
		return;
	}
	list_node *new_node = (list_node *)malloc(sizeof(struct list_node));
    RETURN_IF_NULL(new_node);
    new_node->val = val;

    new_node->next = node;
    new_node->prev = node->prev;
    node->prev->next = new_node;
    node->prev = new_node;
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index)
{
	RETURN_IF_NULL(obj);
	list_node *node = obj->head;
	RETURN_IF_NULL(node);
	int i;
	for (i = 1 ; i <= index ; i++) {
		node = node->next;
		RETURN_IF_NULL(node);
	}
	/*只有一个节点时*/
	if (obj->head == node && obj->tail == node) {
		obj->head = NULL;
		obj->tail = NULL;
		goto out;
	}
	/*多个节点，要free的节点为头节点*/
	if (obj->head == node) {
		obj->head = node->next;
		node->next->prev = NULL;
		goto out;
	}
	/*多个节点，要free的节点为尾节点*/
	if (obj->tail == node) {
		obj->tail = node->prev;
		node->prev->next = NULL;
		goto out;
	}
	/*多个节点，既不是尾节点，也不是头节点*/
	node->prev->next = node->next;
	node->next->prev = node->prev;
out:
	free(node);
	node = NULL;
}

void myLinkedListFree(MyLinkedList* obj)
{
	RETURN_IF_NULL(obj);
	list_node *node = obj->head;
	list_node *prev;
	while(node != NULL) {
		prev = node;
		node = node->next;
		free (prev);
	}
	free(obj);
}

void prinrmylist(MyLinkedList *mylist)
{
    RETURN_IF_NULL(mylist);
    list_node *node = mylist->head;
    printf("mylist : ");
    while(node != NULL)
    {
        printf("%d " , node->val);
        node = node->next;
    }
    printf("\n");
    return;
}

int main()
{
	MyLinkedList *mylist = myLinkedListCreate();
	myLinkedListAddAtHead(mylist, 5);
	myLinkedListAddAtHead(mylist, 2);
	prinrmylist(mylist);
	myLinkedListDeleteAtIndex(mylist, 1);
	prinrmylist(mylist);
	myLinkedListAddAtIndex(mylist, 1, 9);
	prinrmylist(mylist);
	myLinkedListAddAtHead(mylist, 4);
	myLinkedListAddAtHead(mylist, 9);
	myLinkedListAddAtHead(mylist, 8);
	prinrmylist(mylist);
	printf("%d\n", myLinkedListGet(mylist, 3));
	myLinkedListAddAtTail(mylist, 1);
	myLinkedListAddAtIndex(mylist, 3, 6);
	myLinkedListAddAtHead(mylist, 3);
	prinrmylist(mylist);
	return 0;
}

