#include <tut.hpp> 

#include <TySprite.h>
#include <TyScene.h>
#include <TyActor.h>
#include <InheritedActor.h>

namespace tut 
{ 
	struct data //
	{ 
		ITyActor* a;
		CTyScene*	scn;

		data()
		{
			scn = new CTyScene("Test Scene", "A scene for testing!");			
		}

		~data()
		{
			delete scn;
		}
	};
	
	typedef	test_group<data> tg;
	tg test_group("Scene Tests");
	
	typedef tg::object testobject;
	
	template<> 
	template<> 
	void testobject::test<20>() 
	{
		set_test_name("Add Actor");
		a = new InheritedActor();
		ensure_equals("Add actor: ",scn->AddActor(a),true);
	}


	template<>
	template<>
	void testobject::test<21>()
	{
		set_test_name("Delete Actor");
		a = new InheritedActor();
		ensure_equals("Delete Actor (No actors)",scn->DeleteActor(a),false);
		ensure_equals("Add Actor",scn->AddActor(a),true);
		ensure_equals("Delete Actor",scn->DeleteActor(a),true);
	}


	template<>
	template<>
	void testobject::test<22>()
	{
		set_test_name("Create/Destroy Scene");
		a = new InheritedActor();		
		ensure_equals("Create (No actors)",scn->Create(),false);
		ensure_equals("Destroy (No actors)",scn->Destroy(),false);
		ensure_equals("Add Actor",scn->AddActor(a),true);
		ensure_equals("Create",scn->Create(),true);
		ensure_equals("Destroy",scn->Destroy(),true);
	}


	template<>
	template<>
	void testobject::test<24>()
	{
		set_test_name("Play Scene");
		a = new InheritedActor();	

		ensure_equals("Play (No actors)",scn->Play(),false);
		ensure_equals("Add Actor",scn->AddActor(a),true);

		ensure_equals("Play (Not created)",scn->Play(),false);
		ensure_equals("Create", scn->Create(), true);

		ensure_equals("Play",scn->Play(),true);
	}
}; 