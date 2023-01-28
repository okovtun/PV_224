#include<iostream>
#include<string>
using namespace std;

//Product:
class Computer
{
	std::string type;
	std::string cpu;
	std::string ram;
	std::string video;
	std::string disk;
	std::string power;
	bool on;
public:
	void set_type(const std::string& type)
	{
		this->type = type;
	}
	void set_cpu(const std::string& cpu)
	{
		this->cpu = cpu;
	}
	void set_ram(const std::string& ram)
	{
		this->ram = ram;
	}
	void set_video(const std::string& video)
	{
		this->video = video;
	}
	void set_disk(const std::string& disk)
	{
		this->disk = disk;
	}
	void set_power(const std::string& power)
	{
		this->power = power;
	}

	/*Computer(const std::string& cpu, const std::string& ram, const std::string& video, const std::string& disk, const std::string& power) :
		cpu(cpu), ram(ram), video(video), disk(disk), power(power)
	{
		on = false;
		cout << "CConstructor:\t" << this << endl;
	}*/
	Computer()
	{
		on = false;
	}
	virtual ~Computer()
	{
		cout << "CDenstructor:\t" << this << endl;
	}
	virtual void info()const
	{
		cout << "CPU:" << cpu << ", ";
		cout << "RAM:" << ram << ", ";
		cout << "Video:" << video << ", ";
		cout << "Disk:" << disk << ", ";
		cout << "Power:" << power << ";\n";
	}
};

class CheapComputer :public Computer
{
public:
	CheapComputer(const std::string& cpu, const std::string& ram, const std::string& video, const std::string& disk, const std::string& power)
		:Computer(cpu, ram, video, disk, power)
	{
		cout << "CheapComputerConstructor:\t" << this << endl;
	}
	~CheapComputer()
	{
		cout << "CheapComputerDestructor:\t" << this << endl;
	}
};
class OfficeComputer :public Computer
{
public:
	OfficeComputer(const std::string& cpu, const std::string& ram, const std::string& video, const std::string& disk, const std::string& power)
		:Computer(cpu, ram, video, disk, power)
	{
		cout << "OfficeComputerConstructor:\t" << this << endl;
	}
	~OfficeComputer()
	{
		cout << "OfficeComputerDestructor:\t" << this << endl;
	}
};
class GameComputer :public Computer
{
public:
	GameComputer(const std::string& cpu, const std::string& ram, const std::string& video, const std::string& disk, const std::string& power)
		:Computer(cpu, ram, video, disk, power)
	{
		cout << "GameComputerConstructor:\t" << this << endl;
	}
	~GameComputer()
	{
		cout << "GameComputerDestructor:\t" << this << endl;
	}
};


void main()
{
	setlocale(LC_ALL, "");
	//Computer comp("Core i5 12400", "Kingston 8GB", "Intel HD Graphics", "Samsung 870 Evo 500 GB", "Chieftec 500 Gold");
	//comp.info();

	CheapComputer comp("Intel Celeron", "Kingston 4GB", "Intel HD Graphics", "Kingston SSD 128GB", "Chieftec 400");
	comp.info();


}