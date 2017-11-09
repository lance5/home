#pragma once

#include <vector>
#include "CFileManage.h"
#include "CResourceImg.h"
#include <glm/glm.hpp>

struct SModelVector
{
	glm::vec3	m_vPosition;
	glm::vec3	m_vNormal;
	glm::vec2	m_vTexCoords;
};

class CResourceModel
	: public CResourceType
{
	std::vector<CResourceImg>		m_vecTexture;
	std::vector<SModelVector>		m_vecVector;

public:
	CResourceModel( const byte* szBuffer, uint32 nSize );
	~CResourceModel();
};

