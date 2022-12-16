#pragma warning(disable:4326)
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------------\n"

class Tree
{
protected:
	class Element
	{
		int Data;				//Значение элемента
		Element *pLeft, *pRight;//Адреса потомков
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}

	int Count()const
	{
		return Count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg()const
	{
		return (double)Sum(Root) / Count(Root);
	}

	int Depth()const
	{
		return Depth(Root);
	}

	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int Count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return !Root ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}
	int Sum(Element* Root)const
	{
		return !Root ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}

	int Depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		if (Depth(Root->pLeft) < Depth(Root->pRight))return Depth(Root->pRight) + 1;
		else return Depth(Root->pLeft) + 1;
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};
class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "Rus");
#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.Count() << endl;
	cout << "Сумма элементов в дереве: " << tree.Sum() << endl;
	cout << "Среднее-арифметическое элементов в дереве: " << tree.Avg() << endl;
	cout << "Глубина дерева: " << tree.Depth() << endl;

	UniqueTree unique_tree;
	for (int i = 0; i < n; i++)
	{
		unique_tree.insert(rand() % 100);
	}
	unique_tree.print();
	cout << "Минимальное значение в дереве: " << unique_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << unique_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << unique_tree.Count() << endl;
	cout << "Сумма элементов в дереве: " << unique_tree.Sum() << endl;
	cout << "Среднее-арифметическое элементов в дереве: " << unique_tree.Avg() << endl;
	cout << "Глубина дерева: " << unique_tree.Depth() << endl;
#endif // BASE_CHECK

	Tree tree = { 50, 25, 75, 16, 32, 58, 85, 48, 49 };
	tree.print();
	cout << "Глубина дерева: " << tree.Depth() << endl;
}