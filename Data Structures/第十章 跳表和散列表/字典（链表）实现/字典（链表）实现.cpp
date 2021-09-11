#pragma once

#include<iostream>
using namespace std;
/*
��ʹ����ʱ������ָ�룬������pair<K,E>*
���������ͳһʹ��pair<const K,E>*

�ֵ����ֵ�ڵ����
�ֵ�ڵ���pair<> ��nextָ����ɡ�

���캯�������ò�����
*/
//�ֵ�
template<class K, class E>
class dictionary {
public:
	virtual ~dictionary() {}
	virtual bool empty()const = 0;
	virtual int size()const = 0;
	virtual std::pair<K, E>* find(const K&)const = 0;
	virtual void erase(const K&) = 0;
	virtual void insert(const pair<K, E>&) = 0;
};
//�ֵ�ڵ�
template<class K,class E>
struct pairNode {
	using pairType = pair<K, E>;
	pairType element;
	pairNode<K, E>* next;

	pairNode(const pairType node, pairNode<K, E>* n=nullptr) :element(node){
		next = n;
	}
};
//�������������������ֵ�
template<class K,class E>
class sortedChain :public dictionary<K, E> {
private:
	pairNode<K, E>* firstNode;
	int listSize;
public:
	sortedChain() {
		firstNode = nullptr;
		listSize=0;
	}
	bool empty()const override {
		return listSize == 0;
	}
	int size()const override {
		return listSize;
	}
	std::pair<K, E>* find(const K& key)const override {
		pairNode<K, E>* p = firstNode;
		while (p != nullptr && p->element.first != key) {
			p = p->next;
		}
		if (p == nullptr) {
			return nullptr;
		}
		else {
			return &p->element;
		}
	}
	void insert(const pair<K, E>& thePair)override {
		pairNode<K, E>* currentNode = firstNode;
		pairNode<K, E>* preNode = nullptr;

		while (currentNode != nullptr && thePair.first > currentNode->element.first) {
			preNode = currentNode;
			currentNode = currentNode->next;
		}

		if (currentNode != nullptr && currentNode->element.first == thePair.first) {
			currentNode->element.second = thePair.second;
			return;
		}

		pairNode<K, E>* newPair = new pairNode<K, E>(thePair, currentNode);

		if (preNode == nullptr) {
			firstNode = newPair;
		}
		else {
			preNode->next = newPair;
		}
		listSize++;
	}
	void erase(const K& theKey)override {
		if (listSize == 0) {
			clog << "�޷�eraseһ��������" << endl;
			throw runtime_error{ "�޷�eraseһ��������" };
		}
		pairNode<K, E>* currentNode = firstNode;
		pairNode<K, E>* preNode = nullptr;

		while (currentNode != nullptr && theKey > currentNode->element.first) {
			preNode = currentNode;
			currentNode = currentNode->next;
		}
		if (currentNode == nullptr || currentNode->element.first < theKey) {
			clog << "eraseʧ�ܣ�û�����key" << endl;
			return;
		}
		if (preNode == nullptr) {
			firstNode = firstNode->next;
			delete currentNode;
			listSize--;
			return;
		}
		preNode ->next= currentNode->next;
		delete currentNode;
		listSize--;
	}
	void output(ostream& os) const{
		pairNode<K,E>* p = firstNode;
		while (p != nullptr) {
			os << p->element.first << " ";
			p = p->next;
		}
		os << endl;
	}
};
//int main() {
//	sortedChain<int, int> chain{};//����дchain()
//	chain.insert({ 1,1 });
//	chain.output(clog);
//	chain.erase(1);
//	chain.output(clog);
//}