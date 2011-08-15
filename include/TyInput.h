#pragma once

#include <vector>
#include <s3ePointer.h>
#include <IwGxTypes.h>

void TyInputInit();
void TyInputTerminate();

class TyInput;
TyInput* TyGetInput();

struct TyTouch
{
	CIwSVec2		m_Position;
	CIwSVec2		m_LastPosition;
	uint32			m_TouchID;
	bool			m_Active;
	bool			m_Drag;
	s3ePointerState	m_State;	

	TyTouch() : m_Position(CIwSVec2::g_Zero),m_LastPosition(CIwSVec2::g_Zero),m_TouchID(-1),m_Active(false),m_Drag(false),m_State(S3E_POINTER_STATE_UP)
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
	TyTouch*				m_LastTouchDragged;
	bool					m_MultiTouchSupport;

	TyInput();
	~TyInput();
	void CheckForMultitouchSupport();

public:	
	bool		RefreshTouchpad();
	TyTouch		GetTouchInRect(CIwRect pArea, s3ePointerState pState = S3E_POINTER_STATE_DOWN);
	TyTouch		GetLastTouchPressed();
	TyTouch		GetLastTouchReleased();
	TyTouch		GetLastTouchDragged();
};