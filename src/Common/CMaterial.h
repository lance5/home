#pragma once

#include "IUnKnown.h"

enum
{
	eMaterialTexture_Diffuse,
	eMaterialTexture_Bump,
	eMaterialTexture_Specular,
	eMaterialTexture_Count,
};
class CTexture2D;

class CMaterial
{
	DEFAULT_METHOD( CMaterial );

	CVector3f					m_vecAmbient;
	CVector3f					m_vecDiffuse;
	CVector3f					m_vecSpecular;
	float						m_fShininess;
	float						m_fRefractiveIndex;
	float						m_fFadeOut;
	uint8						m_nIllum;
	CTexture2D*					m_Texture[eMaterialTexture_Count];

public:
	CMaterial();
	CMaterial( const CMaterial& p ) = delete;
	~CMaterial();

	void						SetShininess( float f )						{ m_fShininess = f; }
	void						SetAmbient( float x, float y, float z )		{ m_vecAmbient.x = x; m_vecAmbient.y = y; m_vecAmbient.z = z; }
	void						SetDiffuse( float x, float y, float z )		{ m_vecDiffuse.x = x; m_vecDiffuse.y = y; m_vecDiffuse.z = z; }
	void						SetSpecular( float x, float y, float z )	{ m_vecSpecular.x = x; m_vecSpecular.y = y; m_vecSpecular.z = z; }
	void						SetRefractiveIndex( float f )				{ m_fRefractiveIndex = f; }
	void						SetFadeOut( float f )						{ m_fFadeOut = f; }
	void						SetIllum( uint8 n )							{ m_nIllum = n; }

	CTexture2D*					GetTexture( uint8 nTexture );
};