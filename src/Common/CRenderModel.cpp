#include "stdafx.h"
#include "CRenderModel.h"
#include "glad.h"
#include "CGraphics.h"

CRenderModel::CRenderModel()
{
}

CRenderModel::~CRenderModel()
{
	for ( uint32 i = 0; i < m_vecObject.size(); ++i )
	{
		glDeleteVertexArrays( 1, &m_vecObject[i].m_nVertexArrays );
		CheckError();
		glDeleteBuffers( 1, &m_vecObject[i].m_nVertexBuffer );
		CheckError();
	}
}

void CRenderModel::PushObjectData(const std::vector<SVectexData>& vecData, CMaterial * pMaterail, bool bSmooth)
{
	SObject element;
	element.m_bSmooth = bSmooth;
	element.m_Material = pMaterail;
	element.m_nCount = vecData.size();
	pMaterail->AddRef();

	glGenVertexArrays( 1, &element.m_nVertexArrays );
	CheckError();
	glBindVertexArray( element.m_nVertexArrays );
	CheckError();
	glGenBuffers( 1, &element.m_nVertexBuffer );
	CheckError();
	glBindBuffer( GL_ARRAY_BUFFER, element.m_nVertexBuffer );
	CheckError();
	glBufferData( GL_ARRAY_BUFFER, element.m_nCount * sizeof( SVectexData ), (const void*)&vecData[0], GL_STATIC_DRAW );
	CheckError();
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof( SVectexData ), (void*)0 );
	CheckError();
	glEnableVertexAttribArray(1);
	CheckError();
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof( SVectexData ), (void*)(3 * sizeof(float)));
	CheckError();
	glEnableVertexAttribArray(2);
	CheckError();
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof( SVectexData ), (void*)(6 * sizeof(float)));
	CheckError();
	glEnableVertexAttribArray(3);
	CheckError();
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	CheckError();
	glBindVertexArray( 0 );
	CheckError();
	m_vecObject.push_back( element );
}