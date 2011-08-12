#include <tut.hpp> 

#include <TySceneManager.h>
#include <InheritedActor.h>

namespace tut 
{ 
	struct data //
	{ 
		TySceneManager * scnmgr;
		TyScene*	a;

		data()
		{
			scnmgr = TySceneManager::Get();
		}

		~data()
		{
			scnmgr->Erase();
		}
	};
	
	typedef	test_group<data> tg;
	tg test_group("Scene Tests");
	
	typedef tg::object testobject;
	
	template<> 
	template<> 
	void testobject::test<30>() 
	{
		set_test_name("Add Scene");
		a = scnmgr->AddScene();
		ensure_equals("Adds a scene: ",scnmgr->HasScene(a),true);			
	}

	template<> 
	template<> 
	void testobject::test<31>() 
	{
		set_test_name("Delete Scene");
		a = scnmgr->AddScene();
		ensure_equals("Deletes a scene: ",scnmgr->DeleteScene(a),true);		
		ensure_equals("Deleted a scene: ",scnmgr->HasScene(a),false);		
	}

	template<> 
	template<> 
	void testobject::test<33>() 
	{
		set_test_name("Set Active");
		ensure_equals("Set Current Scene (No Scenes): ",scnmgr->SetCurrentScene(a),false);
		ensure_equals("Is Current Scene (No Scenes): ",scnmgr->IsCurrentScene(a),false);
		a = scnmgr->AddScene();
		ensure_equals("Set Current Scene: ",scnmgr->SetCurrentScene(a),true);
		ensure_equals("Is Current Scene: ",scnmgr->IsCurrentScene(a),true);
	}

	template<> 
	template<> 
	void testobject::test<32>() 
	{
		set_test_name("Play Current Scene");
		ensure_equals("Play Current Scene (No Scenes): ",scnmgr->Play(),false);
		a = scnmgr->AddScene();
		a->SetName("Escena de prueba");
		a->AddActor( new InheritedActor() );
		ensure_equals("Set Current Scene: ",scnmgr->SetCurrentScene(a),true);
		ensure_equals("Is Current Scene: ",scnmgr->IsCurrentScene(a),true);
		ensure_equals("Play Current Scene (One Scene): ",scnmgr->Play(),true);
	}
};