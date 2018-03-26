#pragma once

struct SModelData
{
	struct SMaterial
	{
		float						m_fShininess;
		CVector3f					m_vec3Ambient;
		CVector3f					m_vec3Diffuse;
		CVector3f					m_vec3Specular;
		float						m_fRefractiveIndex;
		float						m_fFadeOut;
		uint8						m_nIllum;
		CTexture2D					m_texDiffuse;
		CTexture2D					m_texBump;
		CTexture2D					m_texSpecular;
	};

	struct SObjectIndex
	{
		bool						m_bSmooth;
		std::vector<uint32>			m_vecVertexIndex;
		std::vector<uint32>			m_vecNoramIndex;
		std::vector<uint32>			m_vecTexCoordIndex;
		SMaterial					m_Material;
	};

	std::vector<float>				m_vecVertex;
	std::vector<float>				m_vecNoram;
	std::vector<float>				m_vecTexCoord;
	std::vector<SObjectIndex>		m_vecObject;
}