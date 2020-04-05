#pragma once
#ifndef _DOUBLENODE_H
#define _DOUBLENODE_H
//���ݽṹ�㷨��Ӧ��-C++�������� ������
template<class T>
struct DoubleNode {
	T element;
	DoubleNode<T>* left, *right;

	DoubleNode() {}
	DoubleNode(const T& element){
		this->element = element;
	}
	DoubleNode(const T& element, DoubleNode<T>* left, DoubleNode<T>* right){
		this->element = element;
		this->left = left;
		this->right = right;
	}
};

#endif
