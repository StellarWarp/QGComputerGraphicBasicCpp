#pragma once
#include <iterator>
#include <exception>

//可以考虑让这个类的使用更优雅一点
//不想折腾的删除这个定义
#define LL_ITERATOR_FEATURE ///可选 [迭代器]

#ifndef LL_ITERATOR_FEATURE
template<class T>
struct LinkedListNode
{
	T data{};
	LinkedListNode* next{};
	LinkedListNode* prev{};
};
#endif

template<class T>
class LinkedList
{
private:
#ifdef LL_ITERATOR_FEATURE
	struct Node
	{
		T data{};
		Node* next{};
		Node* prev{};
	};
#else
	using Node = LinkedListNode<T>;
#endif // LL_ITERATOR_FEATURE


	Node* m_front{};//始
	Node* m_back{};//末
	uint64_t m_count;//长度

	//内部插入方法//向后插入
	T* _InsertAfter(const T& data, Node* p_node)
	{
		Node* newnode = new Node;
		newnode->data = data;

		if (m_front)
		{
			//链表插入
			newnode->next = p_node->next;
			if (p_node->next)
				p_node->next->prev = newnode;
			else
				m_back = newnode;
			p_node->next = newnode;
			newnode->prev = p_node;
			m_count++;
		}
		else
		{
			//创建第一节点
			newnode->next = nullptr;
			newnode->prev = nullptr;
			m_front = m_back = newnode;
			m_count = 1;
		}
		return &newnode->data;
	}
	//内部插入方法//向前插入
	T* _InsertBefore(const T& data, Node* p_node)
	{
		Node* newnode = new Node;
		newnode->data = data;

		if (m_front)
		{
			newnode->prev = p_node->prev;
			if (p_node != m_front)
				p_node->prev->next = newnode;
			else
				m_front = newnode;
			p_node->prev = newnode;
			newnode->next = p_node;
			m_count++;
		}
		else
		{
			//创建第一节点
			newnode->next = nullptr;
			newnode->prev = nullptr;
			m_front = m_back = newnode;
			m_count = 1;
		}
		return &newnode->data;
	}
	Node* _Erase(const Node* node) {
		if (!node) return nullptr;//空操作
		if (node == m_front)
		{
			m_front = node->next;
		}
		if (node == m_back)
		{
			m_back = node->prev;
		}
		if (node->prev)
			node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		m_count--;

		if (!m_count) { m_front = m_back = nullptr; }
		auto temp = node->next;
		delete node;
		return temp;
	}
public:
#ifdef LL_ITERATOR_FEATURE
	//迭代器是对指针操作的抽象，外部使用时完全不需要关心指针
	class iterator
	{
	private:
		Node* ptr{};
		iterator(Node* ptr) :ptr(ptr) {}
		friend class LinkedList;
	public:
		using iterator_concept = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		reference operator*() const { return ptr->data; }
		pointer operator->() const { return &ptr->data; }
		iterator& operator++() { ptr = ptr->next; return *this; }
		iterator operator++(int) { iterator tmp = *this; ptr = ptr->next; return tmp; }
		iterator& operator--() { ptr = ptr->prev; return *this; }
		iterator operator--(int) { iterator tmp = *this; ptr = ptr->prev; return tmp; }
		iterator operator+(difference_type i)
		{
			Node* ptr_ = ptr;
			for (auto j = 0; j < i; j++)
				ptr_ = ptr_->next;
			return ptr_;
		}
		iterator operator-(difference_type i)
		{
			Node* ptr_ = ptr;
			for (auto j = 0; j < i; j++)
				ptr_ = ptr_->prev;
			return ptr_;
		}
		bool operator==(const iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const iterator& other) const { return ptr != other.ptr; }
	};

	iterator begin() { return m_front; }
	iterator end() { return nullptr; }
	iterator rbegin() { return m_back; }
	iterator rend() { return nullptr; }
#endif

public:
	LinkedList() {}
	LinkedList(std::initializer_list<T> dataArray)
	{
		for (auto& d : dataArray)
		{
			PushBack(d);
		}
	}
	~LinkedList() { Clear(); }

	T& operator[](uint64_t i) {
		Node* p = m_front;
		for (uint64_t j = 0; j < i; j++)
		{
			p = p->next;
		}
		return p->data;
	}
#ifdef LL_ITERATOR_FEATURE
	//default insert after iter
	void Insert(const T& val, const iterator& iter, bool insert_prev = false) {
		if (insert_prev) _InsertBefore(val, iter.ptr);
		_InsertAfter(val, iter.ptr);
	}
	iterator Erase(const iterator& iter) {
		return _Erase(iter.ptr);
	}
#else
	//default insert after node
	void Insert(const T& val, Node* node, bool insert_prev = false) {
		if (insert_prev) _InsertBefore(val, node);
		_InsertAfter(val, node);
	}
	Node* Erase(const Node* node) {
		return _Erase(node);
	}
	Node* First() { return m_front; }
	Node* Last() { return m_back; }
#endif

	T& Front() { return m_front->data; }
	T& Back() { return m_back->data; }
	void PushFront(const T& val) { _InsertBefore(val, m_front); }
	void PushBack(const T& val) { _InsertAfter(val, m_back); }
	void PopFront() { _Erase(m_front); }
	void PopBack() { _Erase(m_back); }

	size_t Count() { return m_count; }
	bool Empty() { return m_count == 0; }

	void Clear() {
		auto ptr = m_front;
		while (ptr)
		{
			auto del = ptr;
			ptr = ptr->next;
			delete del;
		}
		m_front = m_back = nullptr;
	}

	//... other methods
};