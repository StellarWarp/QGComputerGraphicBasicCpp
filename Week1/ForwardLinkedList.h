#pragma once
#include <iterator>

//可以考虑让这个类的使用更优雅一点
//不想折腾的删除这个定义
//#define FLL_ITERATOR_FEATURE ///可选	[迭代器]

#ifdef FLL_ITERATOR_FEATURE
//这个特性要求在插入和移除时 "在形式上" 无需前一个节点，只使用当前节点即可
//这可以让调用更加优雅
#define FLL_OPTERATE_ON_THIS_FEATURE ///可选 [直接操作]
#endif



template<class T>
class ForwardLinkedList  //双向链表
{
	//...
public:
#ifdef FLL_ITERATOR_FEATURE
	class iterator
	{
	private:
		//...
	public:
		using iterator_concept = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		reference operator*() const;
		pointer operator->() const;
		iterator& operator++();
		iterator operator++(int);
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
		reference operator[](difference_type  i) const;
		auto operator<=>(const iterator&) const = default;
	};

	iterator begin();
	iterator end();
#endif
public:
	ForwardLinkedList();//创建链表
	~ForwardLinkedList();

	T& operator[](int i);//清空链表

#ifdef FLL_ITERATOR_FEATURE
#ifdef FLL_OPTERATE_ON_THIS_FEATURE
	//default insert to the end of the list
	void Insert(const T& val, const iterator& iter = nullptr);
	void Erase(const iterator& iter);
#else
	//default insert to the end of the list
	void Insert(const T& val, const iterator& prev_iter = nullptr);
	void Erase(const iterator& prev_iter);
#endif
#else
	//default insert to the end of the list
	void Insert(const T& val, T* prev_node = nullptr);//默认在链表末尾插入节点
	//default insert to the head of the list
	void Erase(T* prev_node = nullptr);//默认在链表头插入节点
#endif

	T& Front();//指向前一个节点
	T& Back();//指向后一个节点
	void PushFront(const T& val);//前移
	void PushBack(const T& val);//后移
	void PopFront();//删除列表的第一个元素，列表容量减1

	size_t Count();//计数
	bool Empty();//判断链表是否为空

	void Clear();//销毁链表
	void Reverse();//倒序输出

	//... other methods
};