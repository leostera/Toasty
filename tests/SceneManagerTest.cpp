#include <tut.hpp> 

#include <TySceneManager.h>

namespace tut 
{ 
	struct data //
	{ 
		CTySceneManager * scnmgr;
		CTyScene*	a;

		data()
		{
			scnmgr = new CTySceneManager();
		}

		~data()
		{
			delete scnmgr;
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
	void testobject::test<32>() 
	{
		set_test_name("Set Active");
		ensure_equals("Set Current Scene (No Scenes): ",scnmgr->SetCurrentScene(a),false);
		ensure_equals("Is Current Scene (No Scenes): ",scnmgr->IsCurrentScene(a),false);
		a = scnmgr->AddScene();
		ensure_equals("Set Current Scene: ",scnmgr->SetCurrentScene(a),true);
		ensure_equals("Is Current Scene: ",scnmgr->IsCurrentScene(a),true);
	}
};