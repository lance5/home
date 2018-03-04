#pragma once

class CMesh
{
	struct SVertex
	{
		CVector3f	vPosition; 
		CVector3f	vNormal; 
		CVector3f	vTexCoords; 
	};

	struct STexture
	{
		uint32		nID;
		std::string type;
	};

	std::vector< SVertex >	m_vecVertex;
	std::vector< uint32 >	m_vecIndices;
	std::vector< STexture >	m_vecTextures;

public:
	CMesh();
	~CMesh();
};

