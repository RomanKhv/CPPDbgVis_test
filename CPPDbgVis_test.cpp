#include "pch.h"
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/signals2.hpp>

void __fake_code_line()
{}

void test_SmartPointers()
{
	boost::shared_ptr<int> sh;
	sh.reset( new int( 5 ) );

	boost::weak_ptr<int> w;
	w = sh;
}

void test_ptree()
{
	boost::property_tree::wptree t;
//	t.add_child( L"item1", 1 );
}

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

int main()
{
	test_SmartPointers();
	test_ptree();
	test_signals();
}
