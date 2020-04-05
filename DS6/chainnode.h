#pragma once
#ifndef _CHAINNODE_H
#define _CHAINNODE_H
//���ݽṹ�㷨��Ӧ��-C++�������� ������
template<class T>
struct ChainNode {
	T element;
	ChainNode<T>* next;

	ChainNode() {}
	ChainNode(const T& element){
		this->element = element;
	}
	ChainNode(const T& element, ChainNode<T>* next){
		this->element = element;
		this->next = next;
	}

	ChainNode<T>& operator=(const T value){//for Exercise 6
		this->element = value;
		return *this;
	}
};

#endif
