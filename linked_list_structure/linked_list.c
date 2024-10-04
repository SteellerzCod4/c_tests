#include <stdio.h>
#include <stdlib.h>

#define LENGTH 5


typedef struct Node{
	double val;
	struct Node* next;
} Node;

typedef struct LinkedList{
	Node* head;
	Node* tail;
	int length;
} LinkedList;


void linked_list_init(LinkedList* linked_list){
	linked_list->head = NULL;
	linked_list->tail = NULL;
	linked_list->length = 0;
}


void delete_linked_list(LinkedList* linked_list){
	while (linked_list->head != NULL){
		Node* next_head = linked_list->head->next;
		free(linked_list->head);
		linked_list->head = next_head;	
	}
	free(linked_list);
}

Node* push(LinkedList* linked_list, double val){
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (!new_node){
		printf("New Node memroy allocation failure.\n");
		delete_linked_list(linked_list);
		exit(1);
	}
	
	linked_list->length += 1;

	new_node->val = val;
	new_node->next = NULL;

	if (linked_list->head == NULL){
		linked_list->head = new_node;
		linked_list->tail = linked_list->head;
		return new_node;
	}

	Node* prev_tail = linked_list->tail;
	linked_list->tail = new_node;
	prev_tail->next = linked_list->tail;
	return new_node;
}

Node pop(LinkedList* linked_list){
	if (linked_list->tail == NULL){
		printf("LinkedList is empty.\n");
		delete_linked_list(linked_list);
		exit(1);
	}

	linked_list->length -= 1;

	Node popped_node = *(linked_list->tail);
	if (linked_list->head == linked_list->tail){
		free(linked_list->tail);
		linked_list->head = NULL;
		linked_list->tail = NULL;
		return popped_node;
	}
	
	Node* new_tail = linked_list->head;
	while (new_tail->next->next != NULL){
		new_tail = new_tail->next;
	}
	free(linked_list->tail);
	linked_list->tail = new_tail;
	linked_list->tail->next = NULL;
	return popped_node;
}


int insert(LinkedList* linked_list, int pos, double new_val){
	if (pos < 0 || pos > linked_list->length){
		printf("Wrong index.\n");
		delete_linked_list(linked_list);
		exit(1);
	}
	
	if (linked_list->head == NULL || pos == linked_list->length){
		push(linked_list, new_val);
		return 0;
	}

	Node* new_node = (Node*)malloc(sizeof(Node));
	if (!new_node){
		printf("New node allocation in Insert failed.\n");
		delete_linked_list(linked_list);
		exit(1);
	}
	new_node->val = new_val;

	linked_list->length += 1;
	
	Node* current_node = linked_list->head;
	if (pos == 0){
		new_node->next = current_node;
		linked_list->head = new_node;
		return 0;
	}

	while (--pos > 0){
		current_node = current_node->next;
	}
	new_node->next = current_node->next;
	current_node->next = new_node;
	return 0;	
}



void print_linked_list(LinkedList* linked_list){
	Node* current_node = linked_list->head;
	int i = 0;
	while (current_node != NULL){
		printf("(Node: %d, val: %.2lf)\n", i++, current_node->val);
		current_node = current_node->next;
	}
	printf("Total number of nodes: %d\n", linked_list->length);
}



int main(){
	LinkedList* linked_list = (LinkedList*)malloc(sizeof(LinkedList));
	if (!linked_list){
		printf("LinkedList memory allocation failure.\n");
		exit(1);
	}
	linked_list_init(linked_list);
	double values[LENGTH] = {4.21, 3.0, 11, 99.78, 100.0};
	for (int i = 0; i < LENGTH; i++){
		push(linked_list, values[i]);
	}
	print_linked_list(linked_list);
	insert(linked_list, 2, 88);
	print_linked_list(linked_list);
	insert(linked_list, 0, 99);
	print_linked_list(linked_list);
	insert(linked_list, 7, 111);
	print_linked_list(linked_list);
	
	return 0;
}