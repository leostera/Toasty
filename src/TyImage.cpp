#include <TyImage.h>
#include <s3eConfig.h>

TyImage::TyImage(CIwResGroup* pGroup, std::string pName)
{
	bool sameName = ( pName.compare(m_ResourceName) > 0 ) ? true : false;
	bool emptyName = m_ResourceName.empty();
	if( !sameName || m_ResourceGroup != pGroup || !m_Built || ( !emptyName && !m_ResourceGroup) )
	{
		m_ResourceGroup = pGroup;
		m_ResourceName = pName;
		m_Built = false;

		IwGetResManager()->SetCurrentGroup(m_ResourceGroup);
		
		if( m_ResourceGroup->GetResNamed(m_ResourceName.c_str(),IW_GX_RESTYPE_TEXTURE) )
		{				
			m_Built = true;
			m_Image = Iw2DCreateImageResource(m_ResourceName.c_str()); 
			std::string w,h;
			w = m_ResourceName + "_w" ;
			h = m_ResourceName + "_h" ;

			int temp;
			s3eConfigGetInt("Sprites",w.c_str(),&temp);
			m_W = temp;
			s3eConfigGetInt("Sprites",h.c_str(),&temp);
			m_H = temp;
		}		
	}
}

TyImage::~TyImage()
{
	if (m_Built)
		delete m_Image;
}

void TyImage::Render(CIwSVec2 pPosition)
{
	Iw2DDrawImage(m_Image,pPosition);
}