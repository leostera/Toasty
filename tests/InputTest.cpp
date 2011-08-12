#include <tut.hpp> 

#include <TyInput.h>

namespace tut 
{ 
	struct data //
	{ 
		TyInput* a;

		data()
		{
			a = new TyInput();			
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
	void testobject::test<40>() 
	{ 
		set_test_name("KEYS - Refresh the input");
		ensure_equals("Refreshed",a->RefreshKeys(),true);
	}

	template<> 
	template<> 
	void testobject::test<41>() 
	{ 
		set_test_name("KEYS - Is Key Press");
		while ( a->Refresh() )
		{
			if( a->IsKeyPressed() ) break;
		}
		ensure_equals("Last press 'a'",a->GetLastKeyPressed().key,s3eKeyA);
	}
}; 