#include <tut.hpp> 
#include <TyGestures.h>

namespace tut 
{ 
	struct data 
	{ 
		TyGestures* g;
		data()
		{
			g = new TyGestures();
		}

		~data()
		{		
			delete g;
		}
	};
	
	typedef	test_group<data> tg;
	tg testgroup("Gestures Tests Group");
	
	typedef tg::object testobject;
	
	template<> 
	template<> 
	void testobject::test<1>() 
	{ 
		set_test_name("Slide Recon");
		while(TyGetInput()->RefreshTouchpad() && g->Update())
		{
			if ( g->Slide()->Active )
			{
				s3eDeviceYield(500);
				break;
			}
		}
		ensure_equals("Last gesture is Slide", g->LastGesture()->Name, "Slide");
	}	
}; 