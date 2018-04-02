#include "stdafx.h"
#include "CRenderModel.h"
#include "glad.h"

CRenderModel::CRenderModel()
{
	glGenVertexArrays( 1, &m_nVertexArrays );
	glGenBuffers( eBufferType_Count, m_aryVertexBuffer );
	glGenBuffers( eBufferType_Count, m_aryBufferElement );
}

CRenderModel::~CRenderModel()
{
	glDeleteBuffers( eBufferType_Count, m_aryBufferElement );
	glDeleteBuffers( eBufferType_Count, m_aryVertexBuffer );
	glDeleteVertexArrays( 1, &m_nVertexArrays );
}

template<typename Data>
void CRenderModel::SetVertexBuffer( uint8 nType, const Data * pData, uint32 nSize )
{
	glBindVertexArray( m_nVertexArrays );
	glBindBuffer( m_aryVertexBuffer[nType] );
	glBufferData( GL_ARRAY_BUFFER, nSize * sizeof( Data ), (const void*)pData, GL_STATIC_DRAW );
	glBindBuffer( 0 );
	glBindVertexArray(0);
}

template<typename Data>
void CRenderModel::SetBufferElement( uint8 nType, const Data * pData, uint32 nSize )
{
	glBindVertexArray( m_nVertexArrays );
	glBindBuffer( m_aryBufferElement[nType] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, nSize * sizeof( Data ), (const void*)pData, GL_STATIC_DRAW );
	glBindBuffer( 0 );
	glBindVertexArray(0);
}