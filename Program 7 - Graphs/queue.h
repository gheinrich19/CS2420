#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

class Queue{
public:
	Queue(){
		head = NULL;
		tail = NULL;
	}

	void add(EdgeNode g){                        // add a EdgeNode to the queue
		Node* temp = new Node(g);
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

	EdgeNode remove(){                 // remove the head
		EdgeNode g;
		if (head == NULL)
			return g;
		Node* temp;
		temp = head;
		head = head->next;
		removed++;
		size--;
		if (size == 0){
			head = NULL;
			tail = NULL;
		}
		return temp->data;
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