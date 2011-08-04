/*!**********************************************************************************

	\class			ITySingleton
	\brief			Singleton interface.
	\date			2/09/2007
	\version		0.1					
	\author			Leandro Ostera

************************************************************************************/

#pragma once // might be more suitable to use define checks, but pragma once seems to work fine on almost every compiler


template<typename T> class ITySingleton
	{
	private:
		static T*	m_Instance;

	public:
		virtual ~ITySingleton() {
			m_Instance = 0;
		}

		inline static void Erase()
			{
			if( ITySingleton::m_Instance != 0)
				{
				delete m_Instance;
				}
			}

		inline static T* Get()
			{
			if ( ITySingleton::m_Instance == 0 )
				{
				m_Instance = new T;
				}
			return m_Instance;
			}
	};

template <typename T> T* ITySingleton <T>::m_Instance = 0;