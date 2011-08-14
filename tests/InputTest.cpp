#include <tut.hpp> 

#include <TyInput.h>
#include <TyImage.h>
#include <Iw2D.h>

namespace tut 
{ 
	struct data //
	{ 
		TyImage* cubo;
		data()
		{
			IwGetResManager()->LoadGroup("sprites.group");
			cubo = new TyImage(IwGetResManager()->GetGroupNamed("sprites"),"2");
		}

		~data()
		{		
			delete cubo;
			IwGetResManager()->DestroyGroup("sprites");
		}
	};
	
	typedef	test_group<data> tg;
	tg test_group("Input Tests");
	
	typedef tg::object testobject;
	
	template<> 
	template<> 
	void testobject::test<40>() 
	{ 
		set_test_name("TouchPad - Get Touch Press in area (0,0,100,100)");
		
		while ( TyGetInput()->RefreshTouchpad() )
		{
			Iw2DSurfaceClear(0xff000000);
			TyTouch t = TyGetInput()->GetTouchInRect( CIwRect(0,0,100,100) );
			if ( t.m_Active )
			{
				std::cout << "ID: " << t.m_TouchID << std::endl;
				std::cout << "m_Position: " << t.m_Position.x << "," << t.m_Position.y << std::endl;
				ensure_equals("Last press 'a' X", (TyGetInput()->GetLastTouchPressed().m_Position.x >= 0 && TyGetInput()->GetLastTouchPressed().m_Position.x <= 100), true);
				ensure_equals("Last press 'a' Y", (TyGetInput()->GetLastTouchPressed().m_Position.y >= 0 && TyGetInput()->GetLastTouchPressed().m_Position.y <= 100), true);
				cubo->Render(t.m_Position);
				Iw2DSurfaceShow();
				break;
			}
			Iw2DSurfaceShow();
		}
		
	}

	template<>
	template<>
	void testobject::test<41>()
	{
		set_test_name("Touch Dragging");
		//TyImage * pollo= new TyImage(IwGetResManager()->GetGroupNamed("sprites"),std::string("pollo"));
		CIwSVec2 posCubo = CIwSVec2::g_Zero, delta = CIwSVec2::g_Zero;
		bool	pressedCubo = false, moveCubo = false;
		while ( TyGetInput()->RefreshTouchpad() )
		{
			Iw2DSurfaceClear(0xff000000);
			cubo->Render(posCubo);

			TyTouch t = TyGetInput()->GetTouchInRect( CIwRect(posCubo.x,posCubo.y,posCubo.x+cubo->GetSize().x,posCubo.y+cubo->GetSize().y) );
			if ( t.m_Active )
			{				
				pressedCubo = true;								
				if( !(t.m_Position - t.m_LastPosition == CIwSVec2::g_Zero) )
					moveCubo = true;
			}

			if(pressedCubo && moveCubo)
			{
				posCubo = posCubo + (t.m_Position - t.m_LastPosition);
				std::cout << "CUBO - ID: " << t.m_TouchID << std::endl;
				std::cout << "CUBO - m_Position: " << t.m_Position.x << "," << t.m_Position.y << std::endl;				
				std::cout << "CUBO - Position: " << posCubo.x << "," << posCubo.y << std::endl;
				moveCubo = false;
			}
			
			if ( TyGetInput()->GetTouchInRect( CIwRect(0,0,800,600), S3E_POINTER_STATE_RELEASED ).m_Active )
			{
				if(pressedCubo)
				{
					pressedCubo = moveCubo = false;
				}
			}

			Iw2DSurfaceShow();
		}
		
	}

/*
	template<>
	template<>
	void testobject::test<49>() 
	{ 
		set_test_name("PaintGame");
		uint32 colour = 0xffff0000;
		while ( TyGetInput()->RefreshTouchpad() )
		{			
			TyTouch t = TyGetInput()->GetTouchInRect( CIwRect(0,0,480,320) );
			if ( t.m_Active ) //&& TyGetInput()->GetLastTouchPressed().m_TouchID == t.m_TouchID)
			{
				std::cout << "ID: " << t.m_TouchID << std::endl;
				std::cout << "m_Position: " << t.m_Position.x << "," << t.m_Position.y << std::endl;
				switch(t.m_TouchID)
				{
				case 0:
					colour = 0xffff0000;
				break;

				case 1:
					colour = 0xff0000ff;
				break;

				case 2:
					colour = 0x0000ffff;
				break;

				case 3:
					colour = 0x00ffff00;
				break;

				case 4:
					colour = 0xffffffff;
				break;
				}
				Iw2DSetColour(colour);
				Iw2DDrawLine(t.m_Position,t.m_LastPosition);
			}
			Iw2DSurfaceShow();
		}
		
	}
	*/
}; 