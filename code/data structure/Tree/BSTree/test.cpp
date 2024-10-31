#define _CRT_SECURE_NO_WARNINGS  1
#pragma warning(disable:6031)
#include <iostream>
#include "BSTree.h"

using namespace std;
void test()
{
	BSTree<int> bt;
	int arr[] = { 8,3,1,10,6,4,7,14,13 };
	for (auto e : arr)
	{
		bt.Insert(e);
	}
	bt.Pop(10);
	bt.InOrder();
}

int main(void)
{
	test();

	return 0;
}