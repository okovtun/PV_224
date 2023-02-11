#include<iostream>
#include<list>
using std::cin;
using std::cout;
using std::endl;

void main()
{
	setlocale(LC_ALL, "");
	std::list<int> list = { 3,5,8,13,21 };
	for (int i = 0; i < list.size; i++)
	{
		cout << list[i] << "\t";
	}
	cout << endl;
}