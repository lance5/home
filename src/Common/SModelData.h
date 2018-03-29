#pragma once

class CMaterial;
struct SModelData
{
	struct SObjectIndex
	{
		std::string					m_strName;
		bool						m_bSmooth;
		std::vector<uint32>			m_vecVertexIndex;
		std::vector<uint32>			m_vecNoramIndex;
		std::vector<uint32>			m_vecTexCoordIndex;
		CMaterial*					m_Material;

		~SObjectIndex() { SAFE_RELEASE( m_Material ); }
	};

	std::vector<float>				m_vecVertex;
	std::vector<float>				m_vecNormal;
	std::vector<float>				m_vecTexCoord;
	std::vector<SObjectIndex>		m_vecObject;
};