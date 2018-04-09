#pragma once

class CMaterial;
class CGraphics;

struct SVectexData
{
	float	m_vVectex[3];
	float	m_vNormal[3];
	float	m_vTexCoord[2];
};

class CRenderModel
{
	friend CGraphics;
private:
	struct SObject
	{
		uint32						m_nVertexBuffer;
		uint32						m_nCount;
		bool						m_bSmooth;
		CMaterial*					m_Material;
	};

	uint32 m_nVertexArrays;
	std::vector<SObject> m_vecObject;

public:
	CRenderModel();
	~CRenderModel();

	void PushObjectData( const std::vector<SVectexData>& vecData, 
		CMaterial* pMaterail, bool bSmooth );
};
