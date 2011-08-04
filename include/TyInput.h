#pragma once

class TyInput : public TySingleton
{
private:
	struct TyKeys {
		s3eKey		key;
		int64		time;
		bool		down;
	};

	std::vector<TyKeys>		m_Keys;

	struct TyTouchs {
		IwSVec2		pos;
		int64		time;
		bool		down;
		bool		drag;
		IwSVec2		relpos;
	};

	std::vector<TyTouchs>	m_Touchs;

public:	
	~TyInput;

	TyKeys operator () (s3eKey pKey, int64 pTime = 0, bool pDown = true);
	TyKeys operator () (CIwSVec2 pPos, int64 pTime = 0, bool pDown = true);

	void	Refresh();
}