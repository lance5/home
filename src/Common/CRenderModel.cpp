#include "stdafx.h"
#include "CRenderModel.h"
#include "glad.h"

CRenderModel::CRenderModel()
{
	glGenVertexArrays( 1, &m_nVertexArrays );
	glGenBuffers( 1, &m_nVertexBuffer );
}

CRenderModel::~CRenderModel()
{
	for( uint32 i = 0; i < m_vecElement.size(); ++i )
	{
		glDeleteBuffers( eBufferType_Count, m_vecElement[i].m_Element );
	}
	glDeleteBuffers( 1, &m_nVertexBuffer );
	glDeleteVertexArrays( 1, &m_nVertexArrays );
}

template<typename Data>
void CRenderModel::SetVertexBuffer( const Data* aryData[eBufferType_Count],
	const uint32 arySize[eBufferType_Count] )
{
	uint32 nTotleSize = 0;
	for( uint32 i = 0; i < eBufferType_Count; ++i )
		nTotleSize += arySize[i] * sizeof( Data );

	glBindVertexArray( m_nVertexArrays );
	glBindBuffer( GL_ARRAY_BUFFER, m_nVertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, nTotleSize, nullptr, GL_STATIC_DRAW );
	uint32 nCurPos = 0;
	uint32 aryDataSize[] = { 3, 3, 2 };
	for( uint32 i = 0; i < eBufferType_Count; ++i )
	{
		uint32 nCurSize = arySize[i] * sizeof( Data );
		glBufferSubData( GL_ARRAY_BUFFER, nCurPos, nCurSize, &aryData[i] );
		nCurPos += nCurSize;

		glVertexAttribPointer( i, aryDataSize[i], GL_FLOAT, GL_FALSE, aryDataSize[i] * sizeof(float), (void*)nCurPos );
		glEnableVertexAttribArray( i );
	}
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray(0);
}

template<typename Data>
void CRenderModel::PushObjectData( const Data* aryData[eBufferType_Count],
	const uint32 arySize[eBufferType_Count], 
	CMaterial* pMaterail, bool bSmooth )
{
	SObjectElement element;
	element.m_bSmooth = bSmooth;
	element.m_Material = pMaterail;
	pMaterail->AddRef();

	glBindVertexArray( m_nVertexArrays );
	glGenBuffers( eBufferType_Count, element.m_Element );
	for( uint32 i = 0; i < eBufferType_Count; ++i )
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, element.m_Element[i] );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, arySize[i] * sizeof( Data ), (const void*)aryData[i], GL_STATIC_DRAW );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}
	glBindVertexArray( 0 );
	m_vecElement.push_back( element );
}

void CRenderModel::RenderAllObject()
{
	glBindVertexArray( m_nVertexArrays );
	glBindBuffer( GL_ARRAY_BUFFER, m_nVertexBuffer );
	for (uint32 i = 0; i < m_vecElement.size(); ++i)
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_vecElement[i].m_Element[eBufferType_Vertex] );

	}
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );
}