#include <TyInput.h>
#include <string>

TyInput* TyInput::m_Instance = 0;

/*
 *	FRIEND FUNCTIONS IMPLEMENTATIONS
 */

void TyInputInit()
{
	if(!TyInput::m_Instance)
		TyInput::m_Instance = new TyInput();
}

void TyInputTerminate()
{
	if(TyInput::m_Instance)
		delete TyInput::m_Instance;
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
	m_Touches.clear();
}

bool	TyInput::RefreshTouchpad()
{
	s3eResult a = s3ePointerUpdate();

	std::vector<TyTouch>::iterator it;
	for(it = m_Touches.begin(); it != m_Touches.end(); ++it)
	{
		(*it).m_State = s3ePointerGetTouchState( (*it).m_TouchID );
		(*it).m_LastPosition = (*it).m_Position;
		(*it).m_Position = CIwSVec2( (int16)s3ePointerGetTouchX( (*it).m_TouchID ), (int16)s3ePointerGetTouchY( (*it).m_TouchID ) );
		(*it).m_Drag = ( (*it).m_LastPosition == (*it).m_Position ) ? false : true;
		(*it).m_Active = ((*it).m_State != S3E_POINTER_STATE_UNKNOWN)? true : false;
	}

	return (a == S3E_RESULT_SUCCESS) ? true : false;
}

TyTouch TyInput::GetTouchInRect(CIwRect pArea, s3ePointerState pState)
{
	TyTouch t = TyTouch();
	std::vector<TyTouch>::iterator it;
	for(it = m_Touches.begin(); it != m_Touches.end(); ++it)
	{
		if( (*it).m_State == pState )
		{
			if( (*it).m_Position.x >= pArea.x && (*it).m_Position.y >= pArea.y 
				&& (*it).m_Position.x <= pArea.h && (*it).m_Position.y <= pArea.w )
			{
				t = (*it);
				switch( (*it).m_State)
				{
				case S3E_POINTER_STATE_PRESSED :
				case S3E_POINTER_STATE_DOWN :
					if( (*it).m_Drag )
						m_LastTouchDragged = it;
					else
						m_LastTouchPressed = it;						
				break;

				case S3E_POINTER_STATE_UP :
				case S3E_POINTER_STATE_RELEASED :
					m_LastTouchReleased = it;
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
	if (m_MultiTouchSupport )
	{
		m_Touches.reserve( S3E_POINTER_TOUCH_MAX );
		for(int i=0; i<S3E_POINTER_TOUCH_MAX; m_Touches.push_back(TyTouch()), m_Touches.back().m_TouchID=i, ++i);
	}
	else
	{
		m_Touches.push_back(TyTouch());
		m_Touches.back().m_TouchID=0;
	}
}