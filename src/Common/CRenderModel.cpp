#include "stdafx.h"
#include "CRenderModel.h"
#include "glad.h"

CRenderModel::CRenderModel()
{
	glGenVertexArrays( 1, &m_nVertexArrays );
}

CRenderModel::~CRenderModel()
{
	glDeleteVertexArrays( 1, &m_nVertexArrays );
}

void CRenderModel::PushObjectData(const std::vector<SVectexData>& vecData, CMaterial * pMaterail, bool bSmooth)
{
	SObject element;
	element.m_bSmooth = bSmooth;
	element.m_Material = pMaterail;
	element.m_nCount = vecData.size();
	pMaterail->AddRef();

	glBindVertexArray( m_nVertexArrays );
	glGenBuffers( 1, &element.m_nVertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, element.m_nVertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, element.m_nCount * sizeof( SVectexData ), (const void*)&vecData[0], GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof( SVectexData ), (void*)0 );
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof( SVectexData ), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof( SVectexData ), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glBindVertexArray( 0 );
	m_vecObject.push_back( element );
}