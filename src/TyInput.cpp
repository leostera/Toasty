#include <TyInput.h>
#include <TyClock.h>
#include <string>

TyInput* TyInput::m_Instance = 0;

/*
 *	FRIEND FUNCTIONS IMPLEMENTATIONS
 */

void TyInputInit()
{
	if(TyInput::m_Instance == 0)
		TyInput::m_Instance = new TyInput();
}

void TyInputTerminate()
{
	if(TyInput::m_Instance != 0)
		delete TyInput::m_Instance;
	TyInput::m_Instance = 0;
}

TyInput* TyGetInput() 
{
	return TyInput::m_Instance;
}

/*
 *	CLASS METHODS IMPLEMENTATIONS
 */

TyInput::TyInput() : m_MultiTouchSupport(false)
{
	CheckForMultitouchSupport();
}

TyInput::~TyInput()
{
	m_Touches.Delete();
}

bool	TyInput::RefreshTouchpad()
{
	s3eResult a = s3ePointerUpdate();

	CIwManaged** it;
	for(it = m_Touches.GetBegin(); it != m_Touches.GetEnd(); ++it)
	{
		( (TyTouch*) (*it) )->State = s3ePointerGetTouchState( ( (TyTouch*) (*it) )->TouchID );

		( (TyTouch*) (*it) )->LastPosition = ( (TyTouch*) (*it) )->Position;
		( (TyTouch*) (*it) )->Position = CIwSVec2( (int16)s3ePointerGetTouchX( ( (TyTouch*) (*it) )->TouchID ), (int16)s3ePointerGetTouchY( ( (TyTouch*) (*it) )->TouchID ) );	
		( (TyTouch*) (*it) )->TimeSinceLastPress += TyGetClock()->GetTicks();	
		( (TyTouch*) (*it) )->Active = true;

		switch( ( (TyTouch*) (*it) )->State )
		{
		case S3E_POINTER_STATE_PRESSED:			
			( (TyTouch*) (*it) )->FirstPosition = ( (TyTouch*) (*it) )->Position;			
			( (TyTouch*) (*it) )->DeltaPosition = CIwSVec2::g_Zero;		

			if( ( (TyTouch*) (*it) )->DoubleTapCounter == 1)
				( (TyTouch*) (*it) )->TimeSinceLastPress += TyGetClock()->GetTicks();
			else
				( (TyTouch*) (*it) )->TimeSinceLastPress = 0;

			( (TyTouch*) (*it) )->DoubleTapCounter++;
			
			if( ( (TyTouch*) (*it) )->DoubleTapCounter > 2 )
			{
				( (TyTouch*) (*it) )->DoubleTap = true;
				( (TyTouch*) (*it) )->DoubleTapCounter = 0;
			}			
			( (TyTouch*) (*it) )->Drag = false;
		break;
		
		case S3E_POINTER_STATE_DOWN:			
			( (TyTouch*) (*it) )->DeltaPosition = ( (TyTouch*) (*it) )->Position - ( (TyTouch*) (*it) )->LastPosition;		
			if( ( (TyTouch*) (*it) )->DeltaPosition == CIwSVec2::g_Zero )
				( (TyTouch*) (*it) )->Drag = false;
			else
			{
				( (TyTouch*) (*it) )->Drag = true;
			/*	( (TyTouch*) (*it) )->Velocity = CIwSVec2(
					( (TyTouch*) (*it) )->DeltaPosition.x / (int16) TyGetClock()->GetTicks(),
					( (TyTouch*) (*it) )->DeltaPosition.y / (int16) TyGetClock()->GetTicks()); /* watch out! */
			}

			( (TyTouch*) (*it) )->TimeHold += TyGetClock()->GetTicks();
		
			if( ( (TyTouch*) (*it) )->DoubleTapCounter > 0 )
			{
				( (TyTouch*) (*it) )->DoubleTap = false;
				( (TyTouch*) (*it) )->DoubleTapCounter = 0;
			}
		break;

		case S3E_POINTER_STATE_RELEASED:
		case S3E_POINTER_STATE_UP:
			( (TyTouch*) (*it) )->Drag = false;
			( (TyTouch*) (*it) )->DeltaPosition = ( (TyTouch*) (*it) )->Position - ( (TyTouch*) (*it) )->LastPosition;		
			( (TyTouch*) (*it) )->TimeHold = 0;
			( (TyTouch*) (*it) )->Velocity = CIwSVec2::g_Zero;
		break;

		default:
			( (TyTouch*) (*it) )->Active = false;
		break;
		}
	}

	return (a == S3E_RESULT_SUCCESS) ? true : false;
}

TyTouch TyInput::GetTouchInRect(CIwRect pArea, s3ePointerState pState)
{
	TyTouch t = TyTouch(-1);
	CIwManaged** it;
	for(it = m_Touches.GetBegin(); it != m_Touches.GetEnd(); ++it)
	{
		if( ( (TyTouch*) (*it) )->State == pState )
		{
			if( ( (TyTouch*) (*it) )->Position.x >= pArea.x && ( (TyTouch*) (*it) )->Position.y >= pArea.y 
				&& ( (TyTouch*) (*it) )->Position.x <= pArea.h && ( (TyTouch*) (*it) )->Position.y <= pArea.w )
			{
				t = *(TyTouch*)(*it);
				switch( t.State )
				{
				case S3E_POINTER_STATE_PRESSED :
				case S3E_POINTER_STATE_DOWN :
					if( ( (TyTouch*) (*it) )->Drag )
						m_LastTouchDragged = (TyTouch*) (*it);
					else
						m_LastTouchPressed = (TyTouch*) (*it);						
				break;

				case S3E_POINTER_STATE_UP :
				case S3E_POINTER_STATE_RELEASED :
					m_LastTouchReleased = (TyTouch*) (*it);
				break;
				}				
			}
		}
	}
	return t;
}

TyTouch TyInput::GetLastTouchPressed()
{
	TyTouch t = (*m_LastTouchPressed);
	return t;
}

TyTouch TyInput::GetLastTouchReleased()
{
	TyTouch t = (*m_LastTouchReleased);
	return t;
}

TyTouch TyInput::GetLastTouchDragged()
{
	TyTouch t = (*m_LastTouchDragged);
	return t;
}

void TyInput::CheckForMultitouchSupport()
{
	m_MultiTouchSupport = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;
	m_Touches.Add(new TyTouch(0));
	if (m_MultiTouchSupport )
	{
		for(int i=1; i<S3E_POINTER_TOUCH_MAX; m_Touches.Add(new TyTouch(i)), ++i);
	}
}