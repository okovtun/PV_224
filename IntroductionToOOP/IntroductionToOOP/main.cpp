﻿#include<iostream>
using namespace std;

#define tab "\t"

//Создавая класс или структуру мы создаем новый тип данных,
//следовательно, объекты (экземпляры) нашего класса или структуры являются
//самыми обычными переменными.

//				КЛАСС		-	ЭТО ТИП ДАННЫХ
//				СТРУКТУРА	-	ЭТО ТИП ДАННЫХ

class Point
{
	double x;
	double y;
public:
};

void main()
{
	setlocale(LC_ALL, "");
	cout << "Hello OOP" << endl;

	int a;		//Объявление переменной 'a' типа 'int'
	Point A;	//Объявление переменной 'A' типа 'Point'
				//Объявление объекта 'A' структуры 'Point'
				//Объявление экземпляра 'A' структуры 'Point'
	A.x = 2.2;
	A.y = 3.4;
	cout << A.x << tab << A.y << endl;

	Point* pA = &A;
	cout << pA->x << tab << pA->y << endl;
}

/*
-----------------------------------------------------------
.  - Оператор прямого доступа (Point operator)
-> - Оператор косвенного доступа (Arrow operator)
-----------------------------------------------------------
*/

/*
-----------------------------------------------------------
1. Encapsulation - это сокрытие определенной части класса от внешнего мира;
2. Inheritance;
3. Polymorphism;

Модификаторы доступа:

private:	закрытые поля, доступные только внутри класса.
public:		открытые поля, доступные из любого места программы.
protected:	защищенные поля

get/set-методами
get (взять, получить)	- используются для доступа к переменным членам класса на чтение,
						  т.е., позволяют получить (взять) значение закрытой переменной.
set (задать, установить)- используются для доступа к переменным членам класса на запись,
						  т.е., позволяют задать значение закрытой переменной в классе.
						  Кроме того, set-методы обеспечивают фильтрацию данных, т.е., 
						  защищают переменные члены класса от записи в них некорректных 
						  значений.
-----------------------------------------------------------
*/