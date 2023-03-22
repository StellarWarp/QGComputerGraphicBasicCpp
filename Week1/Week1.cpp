#include "LinkedList.h"
#include "ForwardLinkedList.h"
#include <iostream>
#include <format>

//可以在这里写上名字
int main()
{
	LinkedList<int> list{ 1,2,3,4,5,6,7,8,9,10 };

	struct MyStruct {
		int x, y, z;
		bool operator==(const MyStruct& other) { return x == other.x && y == other.y && z == other.z; }
	};

	LinkedList<MyStruct> list_struct{ {1,2,3},{4,5,6},{4,5,6},{7,8,9} };

#ifdef LL_ITERATOR_FEATURE


	std::cout << "\nElements in list\n";
	for (auto& val : list)
	{
		std::cout << val << " ";
		val += 1;
	}

	//the same
	std::cout << "\nElements in list\n";
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		std::cout << *iter << " ";
		*iter -= 1;
	}

	std::cout << "\nElements in list, inverse visit\n";
	for (auto iter = list.rbegin(); iter != list.rend(); iter--)
	{
		std::cout << *iter << " ";
		*iter += 1;
	}

	std::cout << "\nElements in list_struct\n";
	for (auto& val : list_struct)
		std::cout << std::format("x:{} y:{} z:{}\n", val.x, val.y, val.z);

	//same
	std::cout << "\nElements in list_struct\n";
	for (auto iter = list_struct.begin(); iter != list_struct.end(); iter++)
		std::cout << std::format("x:{} y:{} z:{}\n", iter->x, iter->y, iter->z);

	std::cout << "\nErase nearby repeat element in list_struct\n";
	for (auto iter = list_struct.begin(); iter != list_struct.end(); iter++)
	{
		if (iter + 1 != list_struct.end() && *iter == *(iter + 1))
			iter = list_struct.Erase(iter);

		std::cout << std::format("x:{} y:{} z:{}\n", iter->x, iter->y, iter->z);
	}

#else
	std::cout << "\nElements in list\n";
	for (auto pNode = list.First(); pNode != nullptr; pNode = pNode->next)
	{
		std::cout << pNode->data << " ";
		pNode->data += 1;
	}

	std::cout << "\nElements in list, inverse visit\n";
	for (auto pNode = list.Last(); pNode != nullptr; pNode = pNode->prev)
	{
		std::cout << pNode->data << " ";
		pNode->data -= 1;
	}

	std::cout << "\nElements in list_struct\n";
	for (auto pNode = list_struct.First(); pNode != nullptr; pNode = pNode->next)
		std::cout << std::format("x:{} y:{} z:{}\n",
			pNode->data.x, pNode->data.y, pNode->data.z);


	std::cout << "\nErase nearby repeat element in list_struct\n";
	for (auto pNode = list_struct.First(); pNode != nullptr; pNode = pNode->next)
	{
		if (pNode->next != nullptr && pNode->data == pNode->next->data)
			pNode = list_struct.Erase(pNode);

		std::cout << std::format("x:{} y:{} z:{}\n",
			pNode->data.x, pNode->data.y, pNode->data.z);
	}
#endif

}

