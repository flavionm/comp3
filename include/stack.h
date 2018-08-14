#ifndef STACK_H
#define STACK_H

class Stack {
	public:
		Stack();
		~Stack();
		void push(int num);
		int pop();
		const Stack& operator= (const Stack&);
		Stack& operator<< (int num);
		int& operator>> (int& num);

	private:
		int *list;
		int pointer;
		int max;

		void overflow();
		void replaceList(const int newList[], int size);
};

#endif
