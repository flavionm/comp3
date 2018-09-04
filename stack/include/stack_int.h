#ifndef STACK_INT_H
#define STACK_INT_H

class StackInt {
	public:
		StackInt();
		~StackInt();
		void push(int num);
		int pop();
		const StackInt& operator= (const StackInt& s);
		StackInt& operator<< (int num);
		int& operator>> (int& num);

	private:
		int *list;
		int pointer;
		int max;

		void overflow();
		void replaceList(const int newList[], int size);
};

#endif
