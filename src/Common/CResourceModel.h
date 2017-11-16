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
	: public IResourceCallback
{
	std::vector<CResourceImg>		m_vecTexture;
	std::vector<SModelVector>		m_vecVector;
	bool							m_bIsWholeModel;

public:
	CResourceModel();
	~CResourceModel();

	virtual void					OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize );
	bool							IsWholeModel() const { return m_bIsWholeModel; }
};

