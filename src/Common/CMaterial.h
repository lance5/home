#pragma once

enum
{
	eMaterialTexture_Diffuse,
	eMaterialTexture_Bump,
	eMaterialTexture_Specular,
	eMaterialTexture_Count,
};

class CMaterial
{
	float						m_fShininess;
	CVector3f					m_vec3Ambient;
	CVector3f					m_vec3Diffuse;
	CVector3f					m_vec3Specular;
	float						m_fRefractiveIndex;
	float						m_fFadeOut;
	uint8						m_nIllum;
	CTexture2D*					m_aryTexture[eMaterialTexture_Count];

public:
	CMaterial();
	~CMaterial();
};