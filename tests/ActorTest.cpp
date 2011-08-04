#include <tut.hpp> 

#include <TyActor.h>

namespace tut 
{ 
	struct data //
	{ 
		CTyActor * a;
		data()
		{
			a = new CTyActor();
		}

		~data()
		{
			delete a;
		}
	};
	
	typedef	test_group<data> tg;
	tg test_group("Actor Tests");
	
	typedef tg::object testobject;
	
	template<> 
	template<> 
	void testobject::test<1>() 
	{ 
		set_test_name("Building the actor");
		ensure_equals("Is built",a->IsBuilt(),true);
	}	
}; 