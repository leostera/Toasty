#include <TyActor.h>

bool ITyActor::AddState(TySprite* pSprite, TOASTY_ACTOR_STATE pState, TyImage* pMask)
{
	bool toadd = true;
	
	CIwManaged** it = m_States.GetBegin();
	for(; it != m_States.GetEnd(); ++it)
	{
		if( ( (TyState*)(*it) )->State == pState )
		{	
			toadd = false;
			break;
		}
	}

	if( toadd ) 
	{
		m_States.Add( new TyState(pSprite, pState, pMask) );
	}

	return toadd;
}


bool ITyActor::DeleteState(TOASTY_ACTOR_STATE pState)
{
	bool todel = false;
	CIwManaged** it = m_States.GetBegin();

	while( it != m_States.GetEnd() )
	{
		if ( ((TyState*)(*it))->State == pState )
		{
			m_States.Erase(it);
			todel = true;
			break;
		}
		++it;
	}
	return todel;	
}

bool ITyActor::SetCurrentState(TOASTY_ACTOR_STATE pState)
{
	bool toset = false;
	CIwManaged** it;
	for(it = m_States.GetBegin(); it != m_States.GetEnd(); ++it)
	{
		if( ((TyState*)(*it))->State == pState )
		{	
			m_LastState = m_CurrentState;
			m_CurrentState = (TyState*)(*it);
			toset = true;
			break;
		}
	}	
	return toset;
}