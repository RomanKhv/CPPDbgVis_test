#include "pch.h"
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/signals2.hpp>
#include <boost/variant.hpp>

//////////////////////////////////////////////////////////////////////////

class AClass
{
public:
	void foo()
	{}
};

void __fake_code_line()
{}

//////////////////////////////////////////////////////////////////////////

void test_function()
{
	boost::function<void(void)> f;
	f = [](){};
	__fake_code_line();
}

//////////////////////////////////////////////////////////////////////////

void test_SmartPointers()
{
	boost::shared_ptr<int> sh;
	sh.reset( new int( 5 ) );

	boost::shared_ptr<AClass> sh2( new AClass );
	sh2->foo();

	boost::weak_ptr<int> w;
	w = sh;
}

//////////////////////////////////////////////////////////////////////////

void test_optional()
{}

//////////////////////////////////////////////////////////////////////////

void test_ptree()
{
	boost::property_tree::wptree t, t2;
	t.put_value( 1.1 );
	t.put_value( L"string value" );
	t2.put_child( L"child1", t );
	__fake_code_line();
}

//////////////////////////////////////////////////////////////////////////

void test_signals()
{
	boost::signals2::scoped_connection c;
	{
		boost::signals2::signal<void( bool )> s;
		c = s.connect( []( bool ) {} );
		{
			boost::signals2::scoped_connection c2;
			c2 = s.connect( []( bool ) {} );
			__fake_code_line();
		}
		__fake_code_line();
	}
	__fake_code_line();
}

//////////////////////////////////////////////////////////////////////////

void test_variant()
{
	boost::variant<int,bool> v2;
	v2 = 1;
	_ASSERTE( boost::get<int>(v2) == 1 );
	v2 = true;
	_ASSERTE( boost::get<bool>(v2) == true );

	boost::variant<int,bool,std::wstring> v3;
	v3 = 1;
	v3 = std::wstring(L"string");
}

//////////////////////////////////////////////////////////////////////////

int main()
{
	test_function();
	test_optional();
	test_ptree();
	test_signals();
	test_SmartPointers();
	test_variant();
}
