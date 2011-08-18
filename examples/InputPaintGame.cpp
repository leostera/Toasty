#include <Iw2D.h>
#include <TyInput.h>
#include <TyClock.h>
#include <iostream.h>

int main(int argc, char** argv)
{
	Iw2DInit();
	TyClockInit();
	TyInputInit();

	TyTouch t = TyTouch(-1);
	uint32 colour = 0x00000000;
	TyGetClock()->SetCap(30);
	while ( TyGetInput()->RefreshTouchpad() )
	{			
		s3eKeyboardUpdate();
		if ( s3eKeyboardAnyKey() ) break;

		t = TyGetInput()->GetTouchInRect( CIwRect(0,0,480,320), S3E_POINTER_STATE_DOWN );
		if ( t.Active )
		{
			std::cout << "ID: " << t.TouchID << std::endl;
			std::cout << "Position: " << t.Position.x << "," << t.Position.y << std::endl;
			switch(t.TouchID)
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
			Iw2DDrawLine(t.Position,t.LastPosition);			
		}	
		Iw2DSurfaceShow();
		TyGetClock()->Cap();
	}		

	TyInputTerminate();
	TyClockTerminate();
	Iw2DTerminate();

	return 0;
}