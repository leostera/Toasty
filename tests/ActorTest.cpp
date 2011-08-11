#include <tut.hpp> 

#include <InheritedActor.h>
#include <TySprite.h>

namespace tut 
{ 
	struct data //
	{ 
		ITyActor * a;
		CIwResGroup* grp;
		CTySprite*	spr,*spr2;

		data()
		{
			a = new InheritedActor();			
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
	void testobject::test<10>() 
	{ 
		set_test_name("Building the actor");
		ensure_equals("Is built",a->IsBuilt(),true);
	}

	template<>
	template<>
	void testobject::test<11>()
	{
		set_test_name("Add States");
		IwGetResManager()->LoadGroup("sprites.group");
		grp = IwGetResManager()->GetGroupNamed("sprites");
		
		spr = new CTySprite(grp,"1");

		ensure_equals("Added!",a->AddState(spr,TOASTY_ACTOR_ATTACKING),true);
		ensure_equals("Added!",a->AddState(spr,TOASTY_ACTOR_ATTACKING),false);

		delete spr;

		IwGetResManager()->DestroyGroup("sprites");
	}

	template<>
	template<>
	void testobject::test<12>()
	{
		set_test_name("Delete States");

		IwGetResManager()->LoadGroup("sprites.group");
		grp = IwGetResManager()->GetGroupNamed("sprites");
		
		spr = new CTySprite(grp,"1");

		ensure_equals("Added!",a->AddState(spr,TOASTY_ACTOR_ATTACKING),true);
		ensure_equals("Deleteed!",a->DeleteState(TOASTY_ACTOR_ATTACKING),true);
		ensure_equals("Deleteed!",a->DeleteState(TOASTY_ACTOR_ATTACKING),false);

		delete spr;

		IwGetResManager()->DestroyGroup("sprites");
		
	}

	template<>
	template<>
	void testobject::test<13>()
	{
		set_test_name("Set Current State");
		IwGetResManager()->LoadGroup("sprites.group");
		grp = IwGetResManager()->GetGroupNamed("sprites");
		
		spr = new CTySprite(grp,"1");
		spr2 = new CTySprite(grp,"2");

		ensure_equals("Added!",a->AddState(spr,TOASTY_ACTOR_ATTACKING),true);
		ensure_equals("Set!",a->SetCurrentState(TOASTY_ACTOR_ATTACKING),true);
		ensure_equals("State is",a->GetCurrentState(),TOASTY_ACTOR_ATTACKING);

		ensure_equals("Added!",a->AddState(spr2,TOASTY_ACTOR_IDLE),true);
		ensure_equals("Deleteped!",a->DeleteState(TOASTY_ACTOR_ATTACKING),true);
		ensure_equals("Set!",a->SetCurrentState(TOASTY_ACTOR_ATTACKING),false);
		ensure_equals("Set!",a->SetCurrentState(TOASTY_ACTOR_IDLE),true);
		ensure_equals("State is",a->GetCurrentState(),TOASTY_ACTOR_IDLE);
		
		delete spr,spr2;

		IwGetResManager()->DestroyGroup("sprites");
	}
}; 