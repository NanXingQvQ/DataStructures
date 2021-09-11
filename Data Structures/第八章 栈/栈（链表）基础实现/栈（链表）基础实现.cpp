#include<iostream>
using namespace std;

template<class T>
class stack {
	virtual void pop()=0;
	virtual void push(const T& theElement) = 0;
	virtual int size()const = 0;
	virtual bool empty()const = 0;
	virtual T& top() = 0;
};
template<class T>
struct chainNode {
	T element;
	chainNode<T>* pre;
};

template<class T>
class linkedStack :public stack<T> {
private:
	chainNode<T>* stackTop;
	int stackSize;
public:
	linkedStack(int initialNum = 10) {
		if (initialNum < 1) {
			clog << "���캯������Ĳ�����С" << endl;
			throw runtime_error{ "���캯������Ĳ�����С" };
		}
		stackTop = nullptr;
		stackSize = 0;
	}
	~linkedStack() {
		while (stackTop != nullptr) {
			auto ptr = stackTop->pre;////
			delete stackTop;
			stackTop = ptr;
		}
	}
	bool empty()const override {
		return stackSize == 0;
	}
	int size()const override {
		reurn stackSize;
	}
	T& top() {
		if (stackSize == 0) {
			clog << "����top()һ����ջ" << endl;
			throw runtime_error{ "����top()һ����ջ" };
		}
		return stackTop->element;
	}
	void pop()override {
		if (stackSize == 0) {
			clog << "����pop()һ����ջ" << endl;
			throw runtime_error{ "����pop()һ����ջ" };
		}
		auto p = stackTop->pre;
		delete stackTop;
		stackTop = p;
		stackSize--;
	}
};