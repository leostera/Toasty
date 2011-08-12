#pragma once

#include <TySingleton.h>
#include <vector>

class TyInput : public ITySingleton<TyInput>
{
private:
	struct TyKeys {
		s3eKey		key;
		int64		time;
		bool		down;
	};

	std::vector<TyKeys>		m_Keys;
	TyKeys*					m_LastKeyPressed;
	TyKeys*					m_LastKeyReleased;
	TyKeys*					m_LastKeySustained;

	struct TyTouchs {
		IwSVec2		pos;
		int64		time;
		bool		down;
		bool		drag;
		IwSVec2		relpos;
	};

	std::vector<TyTouchs>	m_Touchs;
	TyTouchs*				m_LastTouchPressed;
	TyTouchs*				m_LastTouchReleased;
	TyTouchs*				m_LastTouchSustained;
	TyTouchs*				m_LastTouchDragged;

public:	
	~TyInput();

	TyKeys		GetKeys();
	TyKeys		GetLastKeyPressed();
	TyKeys		GetLastKeyReleased();
	TyKeys		GetLastKeySustained();

	TyTouchs	GetTouchs();
	TyTouchs	GetLastTouchPressed();
	TyTouchs	GetLastTouchReleased();
	TyTouchs	GetLastTouchSustained();
	TyTouchs	GetLastTouchDragged();

	bool		IsKeyPressed(s3eKeys pKey = s3eKeyFirst );
	bool		IsKeyReleased(s3eKeys pKey = s3eKeyFirst );
	bool		IsKeySustained(s3eKeys pKey = s3eKeyFirst , int64 pTime = 0);

	bool		IsTouchPressed(IwSVec2 pPosition = IwSVec2(-1,-1) );
	bool		IsTouchReleased(IwSVec2 pPosition = IwSVec2(-1,-1) );
	bool		IsTouchSustained(IwSVec2 pPosition = IwSVec2(-1,-1) , int64 pTime = 0);
	bool		IsTouchDragged(IwSVec2 pPosition = IwSVec2(-1,-1) , IwSVec2 pRelative = IwSVec2(-1,-1) );

	bool		RefreshTouch();
	bool		RefreshKeys();
	bool		Refresh();
}