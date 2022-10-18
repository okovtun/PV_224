#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

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
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//				Constructors:
	Point()
	{
		x = y = double();
		//double() - значение по умолчанию для типа double
		cout << "Constructor:\t" << this << endl;
	}
	Point(double x)
	{
		this->x = x;
		this->y = 0;
		cout << "1ArgConstructor:" << this << endl;
	}
	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//				Methods:
	void print()const
	{
		cout << "X = " << x << "\tY = " << y << endl;
	}
};

//#define STRUCT_POINT
//#define GET_SET_CHECK

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello OOP" << endl;

#ifdef STRUCT_POINT
	//type name;
	int a;		//Объявление переменной 'a' типа 'int'
	Point A;	//Объявление переменной 'A' типа 'Point'
				//Объявление объекта 'A' структуры 'Point'
				//Объявление экземпляра 'A' структуры 'Point'
	A.x = 2.2;
	A.y = 3.4;
	cout << A.x << tab << A.y << endl;

	Point* pA = &A;
	cout << pA->x << tab << pA->y << endl;
#endif // STRUCT_POINT

#ifdef GET_SET_CHECK
	Point A;
	A.set_x(2);
	A.set_y(3);
	//cout << A.get_x() << tab << A.get_y() << endl;
	A.print();

	Point B;
	B.set_x(5);
	B.set_y(7);
	//cout << B.get_x() << tab << B.get_y() << endl;
	B.print();

	for (int i = 0; i < 10; i++)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // GET_SET_CHECK

	Point A;	//Default constructor
	A.print();

	Point B = 5;//Single-Argument constructor
	B.print();

	Point C(2, 3);
	C.print();
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

/*
-----------------------------------------------------------
					SPECIAL MEMBERS

1. Constructor - это метод, который создает объект;
					-с параметрами;
					-без параметров;
					-по умолчанию (default constructor);
					-конструктор копирования;
					-конструктор переноса;
	Конструктор по умолчанию (Default constructor) - это конструктор, который может быть вызван без параметров.

2. Destructor  - это метод, который уничтожает объект по завершении его времени жизни.
				 Время жизни объекта завршается при выходе за пределы области видимости,
				 в которой он объявлен.
				 ~
				 void
3. Assignment operator;
-----------------------------------------------------------
*/