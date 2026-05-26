
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node {
	uint64_t data;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
} LinkedList;

void Create(LinkedList* list) {
	list->head = NULL;
}

void Destroy(LinkedList* list) {
	Node* current = list->head;
	Node* next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	list->head = NULL;


}

void Push_front(LinkedList* list, uint64_t value) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = value;
	new_node->next = NULL;

	new_node->next = list->head;
	list->head = new_node;


}

Node* Ffind(LinkedList* list, uint64_t value) {
	Node* current = list->head;

	while (current != NULL) {
		if (current->data == value) {
			return current;
		}
		current = current->next;
	}
}

void Pprint(const LinkedList* list) {
	Node* current = list->head;
	Node* next;

	while (current != NULL) {
		printf("%llu ", current->data);
		current = current->next;
	}
}

int main() {
	LinkedList list;
	Node* f;

	Create(&list);

	Push_front(&list, 10);
	Push_front(&list, 20);

	Pprint(&list);

	f = Ffind(&list, 20);

	printf("%llu", f->data);

	Destroy(&list);
	return 0;


}