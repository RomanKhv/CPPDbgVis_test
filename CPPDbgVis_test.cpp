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
{
	std::cout << "\n--- optional ---\n";

	boost::optional<int> o;
	o = boost::none;
	auto init = o.is_initialized();
	std::cout << "is none: " << ((o == boost::none) ? "true" : "false)";
	o.emplace( 7 );
	std::cout << "is none: " << ((o == boost::none) ? "true" : "false");
	init = o.is_initialized();

	std::cout << o.value();
	__fake_code_line();
}

//////////////////////////////////////////////////////////////////////////

void test_ptree()
{
	{
		boost::property_tree::wptree t, t2;
		t.put_value( 1.1 );
		t.put_value( L"string value" );
		t2.put_child( L"child1", t );
		__fake_code_line();
	}
	{
		boost::property_tree::wptree tree;
		boost::property_tree::wptree& root = tree.put( L"root", L"this is root" );

		{
			boost::property_tree::wptree& item1 = root.add( L"array_item", L"item1 value" );
			item1.put( L"name", L"item1" );
			item1.put( L"type", 2 );
			__fake_code_line();
		}
		{
			boost::property_tree::wptree& item2 = root.add( L"array_item", L"" );
			item2.put( L"name", L"item1(2)" );

			boost::property_tree::wptree item22;
			item22.put_value( 2 );
			item2.put_child( L"type", item22 );
			__fake_code_line();
		}
		__fake_code_line();
	}
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
	boost::variant<double> v1;
	v1 = 1.1;

	boost::variant<int,bool> v2;
	v2 = 2;
	_ASSERTE( boost::get<int>(v2) == 2 );
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
