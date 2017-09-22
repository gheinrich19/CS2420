#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

class Queue{
public:
	Queue(){
		head = NULL;
		tail = NULL;
	}

	void add(Board b){                        // add a board to the queue
		Node* temp = new Node(b);
		if (tail == NULL){
			head = temp;
			tail = temp;
		}
		else{
			tail->next = temp;
			tail = tail->next;
		}
		added++;
		size++;
		temp = temp->next = NULL;
		delete temp;
	}

	Board remove(){                 // remove the head
		Board b;
		if (head == NULL)
			return b;
		Node* temp;
		temp = head;
		head = head->next;
		removed++;
		size--;
		return temp->data;
	}

	bool find(Board b){                  // find a board within the queue
		Node* temp = head;
		for (int i = 0; i < size; i++){
			if (b == temp->data)
				return true;
			else
				temp = temp->next;
		}
		return false;
	}

	void empty(){                // empty the queue
		while (size > 0){
			remove();
		}
		tail = NULL;
		removed = 0;
		added = 0;
	}

	int getSize(){
		return size;
	}

	int getAdded(){
		return added;
	}

	int getRemoved(){
		return removed;
	}

private:
	Node* head;
	Node* tail;
	int size = 0;
	int added = 0;
	int removed = 0;
};
#endif