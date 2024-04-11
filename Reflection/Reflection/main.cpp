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
	int bob{10};
public:
	CLASS_INFO(Test, 2, i, bob);
};

int main()
{
	Test test;
	test.Apply(
		[]<typename T>(const T & _arg) 
		{
			std::cout << _arg << " ";
		});
	test.Apply(Print{ Test::Names() });
	test.Apply(SimplePrint{});
	test.Apply(SeparatorPrint{"!"});

	return 0;
}