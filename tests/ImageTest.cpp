#include <tut.hpp> 

#include <TyImage.h>

#define MS_PER_FRAME (1000 / 30)

namespace tut 
{ 
	struct data //
	{ 
		TyImage* s, *s1, *s2;
		CIwResGroup* g;

		data()
		{
			IwGetResManager()->LoadGroup("../examples/data/images.group");
			g = IwGetResManager()->GetGroupNamed("images");
			s = new TyImage(g,"pajaro01");
		}

		~data()
		{
			delete s;
			IwGetResManager()->DestroyGroup("images");			
		}
	};
	
	typedef	test_group<data> tg;
	tg test_group("Image Tests");
	
	typedef tg::object testobject;

	template<> 
	template<> 
	void testobject::test<1>() 
	{ 
		set_test_name("Load the image");
		ensure_equals("Build",s->IsBuilt(),true);
	}	

	template<> 
	template<> 
	void testobject::test<2>() 
	{ 
		set_test_name("Draw the Image");
		s->Render();
		Iw2DSurfaceShow();
		s3eDeviceYield(1000);
	}	

	template<> 
	template<> 
	void testobject::test<3>() 
	{ 
		set_test_name("Copy the Image");

		s1 = new TyImage(g,"pajarogolpe01");
	
		ensure_equals("Both images are built", (s1->IsBuilt() && s->IsBuilt()), true);
		
		int j=0;
	//first render of the original 2 images
		Iw2DSurfaceClear(0xff000000);
		s->Render(CIwSVec2(0,s->GetSize().y));
		s1->Render(CIwSVec2(j,200));
		Iw2DSurfaceShow();
		s3eDeviceYield(1000);
	//Create a new one with the copy constructor
		s2 = new TyImage((*s1));
	//test for self-assignment
		*s1 = *s1;
		ensure_equals("S1 equals S1",s1==s1,true);
	//copy the first one into the second
		*s1 = *s;
	//show them all!
		while(j<100)
		{
			int64 start = s3eTimerGetMs();

			Iw2DSurfaceClear(0xff000000); //paint the screen black

			s->Render(CIwSVec2(0,s->GetSize().y));
			s2->Render(CIwSVec2(200,j));
			s1->Render(CIwSVec2(j,200));
			Iw2DSurfaceShow();
			
			while (s3eTimerGetMs()- start< MS_PER_FRAME)
			{
				int32 yield = (int32) (MS_PER_FRAME - (s3eTimerGetMs()-start));
				if (yield<0)
					break;
				s3eDeviceYield(yield);
			}
			
			++j;
		}
		delete s1,s2;
	}	

	template<> 
	template<> 
	void testobject::test<5>() 
	{ 
		set_test_name("Rotate the Image");
		int j = 0;
		s->Rotate(j);
		ensure_equals("Angle",s->GetAngle(),0);
		while(j<360)
		{
			int64 start = s3eTimerGetMs();
			Iw2DSurfaceClear(0xff000000); //paint the screen black
			s->Render(CIwSVec2(200,200));
			s->Rotate(j*10);
			Iw2DSurfaceShow();			
			while (s3eTimerGetMs()- start< MS_PER_FRAME)
			{
				int32 yield = (int32) (MS_PER_FRAME - (s3eTimerGetMs()-start));
				if (yield<0)
					break;
				s3eDeviceYield(yield);
			}			
			++j;
		}
	}	

	template<> 
	template<> 
	void testobject::test<6>() 
	{ 
		set_test_name("Flip the Image");
		int j = 0;
		s->Flip();
		ensure_equals("Flip (0,0)", s->IsFlipped().x , 0);
		ensure_equals("Flip (0,0)", s->IsFlipped().y , 0);
		while(j<200)
		{
			int64 start = s3eTimerGetMs();
			Iw2DSurfaceClear(0xff000000); //paint the screen black
			s->Render(CIwSVec2(200,200));
			if(j == 50 )
			{
				s->Flip( CIwSVec2(1,0) );
				ensure_equals("Flip (1,0)", s->IsFlipped().x , 1);
			}
			else if(j == 100)
			{
				s->Flip( CIwSVec2(0,1) );
				ensure_equals("Flip (0,1)", s->IsFlipped().y , 1);
			}
			else if(j == 150)
			{
				s->Flip( CIwSVec2(1,1) );
				ensure_equals("Flip (1,1)", s->IsFlipped().x , 1);
				ensure_equals("Flip (1,1)", s->IsFlipped().y , 1);
			}

			Iw2DSurfaceShow();			
			while (s3eTimerGetMs()- start< MS_PER_FRAME)
			{
				int32 yield = (int32) (MS_PER_FRAME - (s3eTimerGetMs()-start));
				if (yield<0)
					break;
				s3eDeviceYield(yield);
			}			
			++j;
		}
	}	
}; 