
#include "Node.h"
class LinkedQueue {
	Node* front;
	Node* rear;
public:
	LinkedQueue() : front(NULL), rear(NULL) {}
	~LinkedQueue() { while (!isEmpty()) delete dequeue(); }
	bool isEmpty() { return front == NULL; } // front가 NULL값이면 큐는 공백상태이다

	void enqueue(Node* p) {
		if (isEmpty()) front = rear = p; //공백 상태일시 front와 rear의 값이 p
		else {
			rear->setLink(p); //rear가 p를 가르키도록 함
			rear = p;
		}
	}
	Node* dequeue() {
		if (isEmpty()) return NULL;
		Node* p = front;
		front = front->getLink();
		if (front == NULL) rear = NULL; //front가 NULL값이면 rear도 NULL값으로 만들어주어야함
		return p;
	}
	Node* peek() { return front; }

};