#pragma once

#include <vector>
#include <s3ePointer.h>
#include <IwGxTypes.h>

struct TyTouch
{
	CIwSVec2		m_Position, m_LastPosition;
	int64			m_TouchID;
	bool			m_Active;
	s3ePointerState	m_State;	

	TyTouch() : m_Position(CIwSVec2::g_Zero),m_LastPosition(CIwSVec2::g_Zero),m_TouchID(-1),m_Active(false),m_State(S3E_POINTER_STATE_UP)
	{ ; }
};

class TyInput
{
private:
	static TyInput*	m_Instance;
	friend void	TyInputInit();
	friend void TyInputTerminate();
	friend TyInput* TyGetInput();

	std::vector<TyTouch>	m_Touches;
	TyTouch*				m_LastTouchPressed;
	TyTouch*				m_LastTouchReleased;
	TyTouch*				m_LastTouchSustained;
	TyTouch*				m_LastTouchDragged;
	bool					m_MultiTouchSupport;

	TyInput();
	~TyInput();

public:	
	bool		RefreshTouchpad();
	TyTouch		GetTouchInRect(CIwRect pArea, s3ePointerState pState = S3E_POINTER_STATE_DOWN);
	TyTouch		GetLastTouchPressed();
};