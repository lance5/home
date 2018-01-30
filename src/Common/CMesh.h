#pragma once

class CMesh
{
	struct SVertex
	{
		vec3	vPosition; 
		vec3	vNormal; 
		vec3	vTexCoords; 
	};

	struct STexture
	{
		uint32 nID;
		string type;
	};

	vector< SVertex >			m_vecVertex;
	vector< uint32 >			m_vecIndices;
	vector< STexture >			m_vecTextures;

public:
	CMesh();
	~CMesh();
};

