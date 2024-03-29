#include<iostream>
using namespace std;
#define tab "\t"

class Element
{
	int Data; //�������� ��������
	Element* pNext; //����� ���������� ��������
	static unsigned int count;//���������� ���������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	explicit operator int()
	{
		return this->Data;
	}
};

unsigned int Element::count = 0;//����������� ���������� ����� ������������������� ������ �� ��������� ������

class ForwardList
{
protected:
	Element* Head;//��������� �� ��������� ������� ������
	//������ �������� ������ ����� � ������
	unsigned int size;
public:
	ForwardList() :Head(nullptr), size(0)
	{
		//����������� �� ��������� ������� ������ ������
		//���� ������ ��������� �� 0 �� ������ ����
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;//�� ������������ ����������� �������� �������� ������������
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) : ForwardList()
	{
		*this = std::move(other);//������� std::move �������� MoveAssignment
		cout << "MoveConstructor:\t" << this << endl;
	}
	ForwardList(std::initializer_list<int> v)
	{
		for (int i : v)
		{
			this->push_back(i);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front();
		/*Element* Temp = Head;
		Element* box = Temp;
		while (Temp)
		{
			Temp = Temp->pNext;
			delete box;
			box = Temp;
		}*/

		cout << "LDestructor:\t" << this << endl;
	}
	//Operators

	ForwardList& operator =(const ForwardList& other)
	{
		if (this == &other)return *this;//���������, ��� ����������� ������ ������
		while (Head)pop_front();//���������, ��� ���������� ������ ������
		//deep copy
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		//Shallow copy:
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	//Adding elements
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
		////10 ������� ����� �������
		//Element* New = new Element(Data);
		////2) �������������� ����� ������� � ������ ������
		//New->pNext = Head;
		////3) ��������� ������ �� ����� �������
		//Head = New;// ��� ������� - ������ �� ��� ������ �������
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		//������ �������� ��������� �� ��������� ������� ������
		//� � ���� ����� ������������ ����� �������
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		//������� ����� ������� 
		//Element* New = new Element(Data);
		//������� �� ������� ��������
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)if (Temp->pNext)Temp = Temp->pNext;
		//�������� ����� ������� � ������
		//New->pNext = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	//Removing elements
	void pop_front()
	{
		//��������� ����� ���������� ��������
		Element* erased = Head;
		//���������������� �� ������
		Head = Head->pNext;
		//������� ������� �� ������
		delete erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//������� �� �������������� �������� ������
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//������� ���������� ������� �� ������
		delete Temp->pNext;
		//�������� ��������� �� ��������� �������
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (Index == size)return pop_back();
		Element* erased = nullptr;
		Element* Temp = Head;
		for (int i = 0; i < Index - 2; i++)
		{
			Temp = Temp->pNext;
		}
		erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete erased;
	}

	//Methods

	void print()const
	{
		cout << "Head:\t" << Head << endl;
		//Element* Temp = Head; //Temp - ��������
		//�������� - ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������
		//while (Temp)
		//{
		//	Temp = Temp->pNext;//������� �� ��������� �������
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ��������� ������: " << Head->count << endl;
	}
	ForwardList reverse()
	{
		ForwardList box{};
		Element* Temp = Head;
		while (Temp)
		{
			box.push_front(Temp->Data);
			Temp = Temp->pNext;
		}
		*this = box;
		return *this;
	}
	Element* begin()
	{
		Element* Temp = Head;
		return Temp;
	}
	Element* end()
	{
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		return Temp->pNext;
	}

	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};



ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;//CopyConstructor
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}



//#define BASE_CHECK
//#define COUNT_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	/*cout << "__________________________" << endl;
	list.push_back(123);
	list.print();
	list.pop_back();*/
	/*int index;
	int value;
	cout << "������� ������ ������������ ��������:"; cin >> index;
	cout << "������� ��������:"; cin >> value;
	list.insert(index, value);
	list.print();
	cout << "������� ������ ���������� ��������:"; cin >> index;
	list.erase(index);
	list.print();*/
	ForwardList list1;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list1.push_back(rand() % 1000);
	}
	list1.print();
	cout << "__________________________" << endl;
	ForwardList list3 = list + list1;
	cout << "__________________________" << endl;
	list3.print();
#endif // BASE_CHECK
#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();

	ForwardList list3;
	list3 = list1 + list2;
	list3.print();
	/*list1.reverse();
	list1.print();*/

#endif // COUNT_CHECK
#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof arr[0]; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
	//range-based for (for ��� ���������, �� ���� ��� ����������)
	for (int i : arr)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY
#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif //RANGE_BASED_FOR_LIST
}