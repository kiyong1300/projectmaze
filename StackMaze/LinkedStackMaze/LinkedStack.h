//c++ 과제였던 LinkedStack class
#include "Node.h"
class LinkedStack 
{
	Node* top;
public:
	LinkedStack() { top = NULL; }
	~LinkedStack() { while (!isEmpty()) delete pop(); }
	bool isEmpty() { return top == NULL; }
	void push(Node* p)
	{
		if (isEmpty()) top = p; //공백 상태일시 p가 top
		else //공백 상태가 아니라면 top을 p로 변경하고 현재의 top을 p다음으로 연결
		{
			p->setLink(top);
			top = p;
		}
	}
	Node* pop()
	{
		if (isEmpty())return NULL; //공백 상태일시 NULL값 반환
		Node* p = top; //top을 p에 저장
		top = top->getLink(); //top을 다음 노드로 수정후에 p값 반환
		return p;
	}
	Node* peek() { return top; } //top값 반환
	void display()
	{
		printf("[LinkedStack]\n");
		for (Node* p = top; p != NULL; p = p->getLink())
			p->display();
		printf("\n");
	}

};
