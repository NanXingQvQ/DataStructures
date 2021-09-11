#include<iostream>
using namespace std;
/*
�˰汾�У�����ʼ��ͷ���ָ�����Ԫ�أ�
β�ڵ�һֱָ���βԪ�ء�

*/
template<class T>
class queue {
public:
	virtual ~queue() {}
	virtual bool empty()const = 0;
	virtual int size()const = 0;
	virtual T& front() = 0;
	virtual T& back() = 0;
	virtual void pop() = 0;
	virtual void push(const T& tehElement) = 0;
};
template <class T>
struct chainNode {
    T element;
    chainNode<T>* next;
    chainNode(const T& element=0, chainNode<T>* next=nullptr) {
        this->element = element;
        this->next = next;
    }
};
template<class T>
class linkedQueue :public queue<T> {
private:
	chainNode<T>* queueFront;
	chainNode<T>* queueBack;
	int queueSize;
public:
	linkedQueue(int initialNum = 10) {
		queueFront = queueBack = nullptr;
		queueSize = 0;
	}
	~linkedQueue() {
		while(queueFront != nullptr) {
			chainNode<T>* p = queueFront->next;
			delete queueFront;
			queueFront = p;
		}
	}
	bool empty()const override {
		return queueSize == 0;
	}
	int size()const override {
		return queueSize;
	}
	void pop() override{
		if (queueSize == 0) {
			clog << "�޷�popһ���ն���" << endl;
			throw runtime_error{ "�޷�popһ���ն���" };
		}
		auto p = queueFront->next;
		delete queueFront;
		queueFront = p;

		queueSize--;
	}
	void push(const T& theElement)override {
		if (size() == 0) {
			queueFront =queueBack= new chainNode<T>(theElement);
			queueSize++;
			return;
		}
		auto p = new chainNode<T>(theElement);
		queueBack->next = p;
		queueBack = p;
		queueSize++;
	}
	T& front() override{
		if (queueSize == 0) {
			clog << "�޷�frontһ���ն���" << endl;
			throw runtime_error{ "�޷�frontһ���ն���" };
		}
		return queueFront->element;
	}
	T& back() override{
		if (queueSize == 0) {
			clog << "�޷�backһ���ն���" << endl;
			throw runtime_error{ "�޷�backһ���ն���" };
		}
		return queueBack->element;
	}
};
int main() {
	linkedQueue<int> a(1);
	a.push(1);
	a.push(2);
	cout << a.size()<<endl;
	a.pop();
	a.pop();
	cout << a.size();
}