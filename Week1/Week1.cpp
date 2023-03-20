#include "LinkedList.h"
#include "ForwardLinkedList.h"
#include <iostream>
#include <format>

//可以在这里写上名字
int main()
{
#ifdef FLL_ITERATOR_FEATURE

	LinkedList<int> list{ 1,2,3,4,5,6,7,8,9,10 };

	std::cout << "Elements in list\n";
	for (auto& val : list)
	{
		std::cout << val << " ";
		val += 1;
	}
	std::cout << std::endl;

	//the same
	std::cout << "Elements in list\n";
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		std::cout << *iter << " ";
		*iter -= 1;
	}
	std::cout << std::endl;

	std::cout << "Elements in list, inverse visit\n";
	for (auto iter = list.rbegin(); iter != list.rend(); iter--)
	{
		std::cout << *iter << " ";
		*iter += 1;
	}
	std::cout << std::endl;

	struct MyStruct {
		int x, y, z;
		bool operator==(const MyStruct& other) { return x == other.x && y == other.y && z == other.z; }
	};

	LinkedList<MyStruct> list_struct{ {1,2,3},{4,5,6},{4,5,6},{7,8,9} };

	std::cout << "Elements in list_struct\n";
	for (auto& val : list_struct)
		std::cout << std::format("x:{} y:{} z:{}\n", val.x, val.y, val.z);
	std::cout << std::endl;

	//same
	std::cout << "Elements in list_struct\n";
	for (auto iter = list_struct.begin(); iter != list_struct.end(); iter++)
		std::cout << std::format("x:{} y:{} z:{}\n", iter->x, iter->y, iter->z);
	std::cout << std::endl;

	std::cout << "Erase nearby repeat element in list_struct\n";
	for (auto iter = list_struct.begin(); iter != list_struct.end(); iter++)
	{
		if (iter + 1 != list_struct.end() &&*iter == *(iter + 1)) 
			iter = list_struct.Erase(iter);

		std::cout << std::format("x:{} y:{} z:{}\n", iter->x, iter->y, iter->z);
	}
	std::cout << std::endl;


#endif

}

