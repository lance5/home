#pragma once

#include "TypeDef.h"
#include "glm\vec3.hpp"
using namespace glm;

#include <string>
#include <vector>
using namespace std;

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

