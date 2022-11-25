#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
#include<thread>
using namespace std;

namespace Geometry
{
	bool finish = false;
	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000AAFF,
		white = 0x00FFFFFF,
		grey = 0x00AAAAAA,

		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE,
	};

	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
		std::thread draw_thread;
	public:
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			if (start_x > 800)start_x = 800;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y > 500)start_y = 500;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width > 30)line_width = 30;
			this->line_width = line_width;
		}
		Shape(unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape()
		{
			//if (draw_thread.joinable())draw_thread.join();
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimeter() << endl;
			//draw();
			//start_draw();
			//draw_thread = std::thread(&Shape::start_draw, *this);
		}
		void start_draw()
		{
			while (!finish)
			{
				draw();
				start_x++;
				start_y++;
				Sleep(500);
			}
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < 5)side = 5;
			if (side > 20)side = 20;
			this->side = side;
		}
		//				Constructors:
		Square(double side, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :
			Shape(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~Square() {}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата: " << side << endl;
			Shape::info();
		}
	};
	class Rectangle :public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width < 30)width = 30;
			if (width > 300)width = 300;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length < 20)length = 20;
			if (length > 200) length = 200;
			this->length = length;
		}
		Rectangle(double width, double length, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle()
		{
			if (draw_thread.joinable())draw_thread.join();
		}
		double get_area()const override
		{
			return width * length;
		}
		double get_perimeter()const override
		{
			return (width + length) * 2;
		}
		void draw()const
		{
			/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < length; i++)
			{
				for (int j = 0; j < width; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);*/

			//1) Получаем окно консоли:
			HWND hwnd = GetConsoleWindow();
			//2) Получаем контекст устройства для окна консоли:
			HDC hdc = GetDC(hwnd);	//это то, на чем мы будем рисовать

			//3) Создаем карандаш - это то, чем мы будем рисорвать (карандаш рисует линии):
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			//4) Создаем кисть. Кисть рисует заливку в замкнутой фигуре
			HBRUSH hBrush = CreateSolidBrush(color);
			//5) Выбираем чем, и на чем мы будем рисорвать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) Рисуем прямоугольник:
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);

			//Удаляем карандаш:
			DeleteObject(hPen);
			DeleteObject(hBrush);

			//Освобождаем контекст устройства:
			ReleaseDC(hwnd, hdc);
		}
		void info()override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << width << endl;
			cout << "Длина:  " << length << endl;
			Shape::info();
			this->draw_thread = std::thread(&Shape::start_draw, this);
		}
	};
	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			if (radius < 20)radius = 20;
			if (radius > 220)radius = 220;
			this->radius = radius;
		}
		Circle(double radius, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color)
		{
			set_radius(radius);
		}
		~Circle()
		{
			if (draw_thread.joinable())draw_thread.join();
		}
		double get_area()const override
		{
			return M_PI * radius*radius;
		}
		double get_perimeter()const override
		{
			return 2 * M_PI*radius;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color - 0x00555555);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + radius * 2, start_y + radius * 2);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		/*void start_draw()const
		{
			while (true)
			{
				draw();
			}
		}*/
		void info() override
		{
			cout << typeid(*this).name() << endl;
			cout << "Radius:\t" << radius << endl;
			Shape::info();
			this->draw_thread = std::thread(&Shape::start_draw, this);
		}
	};
	class Triangle :public Shape
	{
	public:
		Triangle(unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color) {}
		virtual double get_height()const = 0;
		void info()
		{
			cout << "Height:\t" << get_height() << endl;
			Shape::info();
		}
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < 20)side = 20;
			if (side > 200)side = 200;
			this->side = side;
		}
		EquilateralTriangle(double side, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~EquilateralTriangle()
		{
			if (draw_thread.joinable())draw_thread.join();
		}
		double get_height()const override
		{
			return 2 * get_area() / side;
		}
		double get_area()const override
		{
			return side * side*sqrt(3) / 4;
		}
		double get_perimeter()const override
		{
			return side * 3;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);

			HBRUSH hBrush = CreateSolidBrush(color-0x00555555);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vert[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};
			::Polygon(hdc, vert, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		/*void start_draw()const
		{
			while (true)
			{
				draw();
			}
		}*/
		void info()
		{
			cout << typeid(*this).name() << endl;
			cout << "Side:\t" << side << endl;
			Triangle::info();
			this->draw_thread = std::thread(&Shape::start_draw, this);
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape;
	Geometry::Square square(8, 100, 100, 11, Geometry::Color::console_red);
	//square.info();

	Geometry::Rectangle rect(150, 70, 300, 100, 11, Geometry::Color::red);
	rect.info();

	Geometry::Circle circle(100, 500, 100, 11, Geometry::Color::yellow);
	circle.info();

	Geometry::EquilateralTriangle e_try(170, 350, 200, 8, Geometry::Color::green);
	e_try.info();

	/*std::thread e_try_thread(&Geometry::EquilateralTriangle::start_draw, e_try);
	std::thread circle_thread(&Geometry::Circle::start_draw, circle);
	circle_thread.join();
	e_try_thread.join();*/
	cin.get();
	Geometry::finish = true;
}