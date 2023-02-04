#include<iostream>
#include<string>
using namespace std;

typedef int Cable;

//Adaptee source interface
class EuropeanSocketInterface
{
public:
	virtual int voltage() = 0;

	virtual Cable live() = 0;		//Фаза
	virtual Cable neutral() = 0;	//0
	virtual Cable earth() = 0;		//Заземление
};

//Adaptee
class Socket :public EuropeanSocketInterface
{
	int voltage()override
	{
		return 220;
	}

	Cable live()override
	{
		return 1;
	}
	Cable neutral()
	{
		return -1;
	}
	Cable earth()
	{
		return 0;
	}
};

//Target interface:
class USASocketInterface
{
public:
	virtual int voltage() = 0;

	virtual Cable live() = 0;
	virtual Cable neutral() = 0;
};

//The Adapter:
class Adapter :public USASocketInterface
{
	EuropeanSocketInterface* socket;

public:
	void plugIn(EuropeanSocketInterface* outlet)
	{
		socket = outlet;
	}

	int voltage()
	{
		return 110;
	}
	Cable live()
	{
		return socket->live();
	}
	Cable neutral()
	{
		return socket->neutral();
	}
};

//Client:
class ElectricKettle
{
	USASocketInterface* power;
public:
	void plugIn(USASocketInterface* supply)
	{
		power = supply;
	}

	void boil()
	{
		if (power->voltage() > 110)
		{
			cout << "Alarm: Kettle is on fire" << endl;
			return;
		}
		if (power->live() == 1 && power->neutral() == -1)
		{
			cout << "Have a nice coffee" << endl;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");

	Socket* socket = new Socket;
	Adapter* adapter = new Adapter;
	ElectricKettle* kettle = new ElectricKettle;

	adapter->plugIn(socket);
	kettle->plugIn(adapter);

	kettle->boil();
}