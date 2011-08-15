#include <TyImage.h>
#include <s3eConfig.h>

bool	TyImage::operator== (TyImage const& pImage) const
{
	bool value = false;
	if(this->GetResourceName().compare(pImage.GetResourceName())
		&& this->GetResourceGroup() == pImage.GetResourceGroup() )
		value = true;
	return value;		
}

TyImage&	TyImage::operator = (TyImage const& pImage)
{
	if(this != &pImage)
	{
		if(pImage.IsBuilt())
		{
			if(m_Built)
				delete m_Image;
			m_Built = false;

			LoadFromResource(pImage.GetResourceGroup(),pImage.GetResourceName());
			
			m_Size = pImage.GetSize();
		}		
	}
	return (*this);
}

TyImage::TyImage(CIwResGroup* pGroup, std::string pName)
	: m_Built(false)
{
	LoadFromResource(pGroup,pName);
}

TyImage::~TyImage()
{
	if(m_Built)
		delete m_Image;
	m_Built = false;
}

TyImage::TyImage(TyImage const& pImage)
: m_Built(false), m_Size(pImage.GetSize())
{
	if(pImage.IsBuilt())
	{
		if(m_Built)
			delete m_Image;
		LoadFromResource(pImage.GetResourceGroup(),pImage.GetResourceName());		
	}			
}

bool TyImage::LoadFromResource(CIwResGroup* pGroup, std::string pName)
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
			m_Size.x = m_Image->GetWidth();
			m_Size.y = m_Image->GetHeight();
			m_Center.x = m_Size.x / 2;
			m_Center.y = m_Size.y / 2;
			m_Angle = 0;
			m_Flip = CIwSVec2::g_Zero;
		}		
	}
	return m_Built;
}

void TyImage::Render(CIwSVec2 pPosition)
{
	if(m_Angle > 0 || m_Angle < 0)
	{
		CIwMat2D RotationMatrix;
		RotationMatrix.SetRot(m_Angle, CIwVec2(pPosition.x + m_Center.x , pPosition.y + m_Center.y) );
		Iw2DSetTransformMatrix(RotationMatrix);
	}

	if( m_Flip.x > 0 && m_Flip.y > 0)
		Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_ROT180);
	else if( m_Flip.x > 0 && m_Flip.y <= 0)
		Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_FLIP_X);	
	else if( m_Flip.y > 0 && m_Flip.x <= 0)
		Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_FLIP_Y);

	Iw2DDrawImage(m_Image,pPosition);

	if(m_Angle > 0 || m_Angle < 0)
		Iw2DSetTransformMatrix(CIwMat2D::g_Identity);
	if( m_Flip.x > 0 || m_Flip.y > 0)
		Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_NONE);
}

void TyImage::Rotate(iwangle pRads)
{
	m_Angle = pRads;
}

void TyImage::Center(CIwSVec2 pCenter)
{
	m_Center = pCenter;
}

void TyImage::Flip(CIwSVec2 pFlip)
{
	m_Flip.x = pFlip.x;
	m_Flip.y = pFlip.y;
}