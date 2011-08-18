#include <TyScene.h>

TyScene::TyScene(std::string pName, std::string pCaption, std::string pResGroup, int64 pID, bool pZOrdered)
	:	m_Name(pName), m_Caption(pCaption), m_ID(pID), m_ZOrdered(pZOrdered), m_Created(false)
{
	if(! pResGroup.empty())
	{	
		m_ResGroupName = pResGroup;
		m_ResGroup = IwGetResManager()->GetGroupNamed(m_ResGroupName.c_str());
	}
}

TyScene::~TyScene()
{
	m_Actors.Delete();
}

bool	TyScene::AddActor(ITyActor* pActor) //adds an actor
{
	m_Actors.Add(pActor);
	return (m_Actors.Find(pActor))?true:false;
}

bool	TyScene::DeleteActor(ITyActor* pActor) //adds an actor
{
	uint32 tofind = m_Actors.Find( pActor );
	if( tofind )
	{		
		m_Actors.EraseFast( tofind );
	}
	return tofind?true:false;
}

bool		TyScene::Create()
{
	m_Created = false;
	CIwManaged** it;
	for(it = m_Actors.GetBegin(); it != m_Actors.GetEnd(); ++it)
	{
		m_Created = ( (ITyActor*)(*it) )->OnCreate();
		//if( !m_Created ) break; //add exception to show which actor failed to create!
	}
	return m_Created;
}

bool		TyScene::Destroy()
{
	bool Destroyed = false;
	CIwManaged** it;
	for(it = m_Actors.GetBegin(); it != m_Actors.GetEnd(); ++it)
	{
		Destroyed = ( (ITyActor*)(*it) )->OnDestroy();		
	}	
	if( Destroyed ) m_Created = false;
	return Destroyed;
}

bool		TyScene::Play()
{
	bool playing = false;
	if( m_Created && m_Actors.GetSize()>0 )
	{
		playing = true;

		CIwManaged** it;

		for( it = m_Actors.GetBegin(); it != m_Actors.GetEnd(); ++it )
		{
			if( ((ITyActor*)(*it))->IsActive() )
				( (ITyActor*)(*it) )->OnStepStart();
		}

/*		for( it = m_Actors.GetBegin(); it != m_Actors.GetEnd(); ++it )
		{
			if( ((ITyActor*)(*it))->IsActive() )
			{
				( (ITyActor*)(*it) )->OnKeyPress();
				( (ITyActor*)(*it) )->OnKeySustain();
				( (ITyActor*)(*it) )->OnKeyRelease();
				( (ITyActor*)(*it) )->OnTouchPress();
				( (ITyActor*)(*it) )->OnTouchSustain();
				( (ITyActor*)(*it) )->OnTouchDrag();
				( (ITyActor*)(*it) )->OnTouchRelease();
			}
		} */
		
		for( it = m_Actors.GetBegin(); it != m_Actors.GetEnd(); ++it )
		{
			if( ((ITyActor*)(*it))->IsActive() )
				( (ITyActor*)(*it) )->OnStep();
		}

		for( it = m_Actors.GetBegin(); it != m_Actors.GetEnd(); ++it )
		{
			if( ((ITyActor*)(*it))->IsActive() )
				( (ITyActor*)(*it) )->OnIntersectBoundaries(m_Boundaries);

			if( ((ITyActor*)(*it))->IsSolid() )
				for( CIwManaged** it2 = m_Actors.GetBegin(); it2 != m_Actors.GetEnd(); ++it2 )
					( (ITyActor*)(*it) )->OnCollision( *((ITyActor*)(*it2)) );
		}

		for( it = m_Actors.GetBegin(); it != m_Actors.GetEnd(); ++it )
		{
			if( ((ITyActor*)(*it))->IsVisible() )
				( (ITyActor*)(*it) )->OnRender();
			if( ((ITyActor*)(*it))->IsActive() )
				( (ITyActor*)(*it) )->OnStepEnd();
		}
	}
	return playing;
}
