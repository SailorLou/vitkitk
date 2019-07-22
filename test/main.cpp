#include <iostream>
class BaseClass
{
public:
	virtual void v() {};
	virtual void b() {};
};

class DerivedClass:public BaseClass
{
public:
};

void main()
{
	BaseClass base;
	DerivedClass subclass;

	std::cout <<"BaseClass::v ="<< &BaseClass::v << std::endl;
	std::cout <<"DerivedClass::v = "<< &DerivedClass::v << std::endl;

	std::cout << "BaseClass::b =" << &BaseClass::b << std::endl;
	std::cout << "DerivedClass::b = " << &DerivedClass::b << std::endl;


	getchar();
}