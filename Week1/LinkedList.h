#pragma once
#include <iterator>
#include <iostream>
using namespace std;
//可以考虑让这个类的使用更优雅一点
//不想折腾的删除这个定义
//#define LL_ITERATOR_FEATURE ///可选 [迭代器]

template<class T>

class Node//链表节点类
{
public:
	T data;//存放数据
	Node<T>* next;
	Node();
	Node(T data);
};

template<class T>

Node<T>::Node() {};//无参构造函数

template<class T>

Node<T>::Node(T data)
{
	this->data = data;//有参数构造函数
}

template<class T>

class LinkedList  //单向链表
{
private:
	Node<T>* head;
	int size = 0;//记录节点数量

public:
#ifdef LL_ITERATOR_FEATURE
	class iterator
	{
	private:
		//...
	public:
		using iterator_concept = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		reference operator*() const;
		pointer operator->() const;
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
		reference operator[](difference_type  i) const;
		auto operator<=>(const iterator&) const = default;
	};

	iterator begin();
	iterator end();
	iterator rbegin();
	iterator rend();
#endif

public:
	LinkedList();//链表的构造函数
	~LinkedList();//链表的析构函数

	T& operator[](int i);//清空链表

#ifdef LL_ITERATOR_FEATURE
	//default insert after iter
	void Insert(const T& val, const iterator& iter, bool insert_prev = false);
	iterator Erase(const iterator& iter);
#else
	//default insert after node
	//void Insert(const T& val, T* node, bool insert_prev = false);
	void Insert(int i,int pos)//节点后插入
	//T* Erase(T* node);
#endif

	T& Front();
	T& Back();
	//void PushFront(const T& val);
	//void PushBack(const T& val);
	void PopFront();//删除列表的第一个元素
	void PopBack();//删除列表的最后一个元素
	void Erase(int pos);//删除指定位置的节点
	size_t Count();//获取链表节点数
	bool Empty();//判断链表是否为空

	void Clear();//销毁链表

	void PushFront(Node<T>* node);

	void PushBack(Node<T>* node);
	void Print();
	//... other methods
};

template<class T>

//实现构造函数
LinkedList<T>::LinkedList()
{
	head = new Node<T>();
	head->next = NULL;
	head->data = 0;
}

template<class T>

//析构函数
LinkedList<T>::~LinkedList()
{
	Clear();
}
template<class T>
void Clear()//销毁链表
{
	Node<T>* tempNode = head->next;
	while (tempNoed != NULL) {
		Node<T>* deleteNode = tempNode;
		tempNode = tempNode->next;
		delete deleteNode;
	}
	delete head;
}
template<class T>
//在链表头插入节点
void LinkedList<T>::PushFront(Node<T>* node) {
	val->next = head->next;
	head->next = val;
	size++;
}
template<class T>
//在链表尾插入节点
void PushBack(Node<T>* node) {
	Node<T>* tempNode = head;
	while (tempNode-> != NULL) {//遍历链表，找到表尾
		tempNode = tempNode->next;
	}
	tempNode->next = val;
	size++;
}
template<class T>
//获取链表节点数
size_t Count() {
	return size;

}
template<class T>
//判断链表是否为空
bool Empty() {
	return ( size == 0) ? true : false;
}
template<class T>
//删除指定位置的节点
void LinkedList<T>::Erase(int pos)//删除指定位置pos的结点
{
	Node<T>* EraseNode = head;
	Node<T>* tempNode;
	cout << "delete data position: " << pos << endl;
	if (pos == 1)
	{
		head = head->next;
		free(EraseNode);
		return;
	}

	for (int i = 0; i < pos - 1; i++)
	{
		EraseNode = EraseNode->next;
	}

	tempNode = EraseNode->next;
	EraseNode->next = tempNode->next;
	free(tempNode);

	size--;
}
template<class T>
void LinkedList<T>::Print()//顺序输出链表所有元素
{
	Node<T>* tempNode = head;
	cout << "the data in list:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << tempNode->next->data << endl;
		tempNode = tempNode->next;
		if (tempNode->next == NULL)
		{
			return;
		}
	}
}
