#include <iostream>
#include "Reflection.h"

template<typename NamesArray>
struct Print
{
	NamesArray m_Array;
	int counter{ 0 };
	template<typename T>
	void operator()(const T& _arg)
	{
		std::cout << m_Array[counter++] << ": " << _arg << std::endl;
	}
};

struct SimplePrint
{
	template<typename T>
	void operator()(const T& _arg)
	{
		std::cout << _arg << std::endl;
	}
};

struct SeparatorPrint
{
	const char* m_Seperator;
	template<typename T>
	void operator()(const T& _arg)
	{
		std::cout << _arg << m_Seperator;
	}
};

class Test
{
	int i{5};
	int bob{ 10 };
	float bob2{10};
public:
	CLASS_INFO(Test, 3, i, bob, bob2);
};

class Foo
{
	int Boo{10};
	float Hoo{5.5f};
	int Goo{20};
	bool Woo{false};
public:
	CLASS_INFO(Foo, 4, Boo, Hoo, Goo, Woo);
};

int main()
{
	Foo obj;
	obj.Apply(Print{ obj.Names() });
	obj.Apply(SimplePrint{});
	return 0;
}