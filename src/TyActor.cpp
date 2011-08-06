#include <TyActor.h>

bool ITyActor::AddState(CTySprite* pSprite, TOASTY_ACTOR_STATE pState)
{
	bool toadd = true;
	std::vector<CTyState>::iterator it;

	for(it = m_States.begin(); it != m_States.end(); ++it)
	{
		if( (*it).state == pState )
		{	
			toadd = false;
			break;
		}
	}

	if( toadd ) 
		m_States.push_back( CTyState(pSprite, pState) );

	return toadd;
}


bool ITyActor::DeleteState(TOASTY_ACTOR_STATE pState)
{
	bool todel = false;
	std::vector<CTyState>::iterator it;
	for(it = m_States.begin(); it != m_States.end(); ++it)
	{
		if( (*it).state == pState  &&  m_CurrentState != it )
		{
			m_States.erase(it);
			todel = true;
			break;
		}
	}
	return todel;	
}

bool ITyActor::SetCurrentState(TOASTY_ACTOR_STATE pState)
{
	bool toset = false;
	std::vector<CTyState>::iterator it;
	for(it = m_States.begin(); it != m_States.end(); ++it)
	{
		if( (*it).state == pState )
		{	
			m_LastState = m_CurrentState;
			m_CurrentState = it;
			toset = true;
			break;
		}
	}	
	return toset;
}