#include "stdafx.h"
#include "CTexture2D.h"
#include "glad.h"
#include "CGraphics.h"

CTexture2D::CTexture2D()
	: m_nTextureID( 0 )
	, m_nRef( 1 )
{
	glGenTextures( 1, &m_nTextureID );
	CheckError();
}

CTexture2D::~CTexture2D()
{
	glDeleteTextures( 1, &m_nTextureID );
	CheckError();
	m_nTextureID = 0;
}

void CTexture2D::SetTextureData( uint8 nFormat, uint32 nWidth, uint32 nHeight, const byte* pData )
{
	if ( m_nTextureID == 0 )
		return;
	GLint nInternalFormat;
	switch( nFormat )
	{
	case eIF_RED:
		nInternalFormat = GL_RED;
		break;
	case eIF_RGB:
		nInternalFormat = GL_RGB;
		break;
	case eIF_RGBA:
		nInternalFormat = GL_RGBA;
		break;
	case eIF_INVALID:
		return;
	}
	glBindTexture( GL_TEXTURE_2D, m_nTextureID );
	CheckError();
	glTexImage2D( GL_TEXTURE_2D, 0, nInternalFormat, nWidth,
		nHeight, 0, nInternalFormat, GL_UNSIGNED_BYTE, pData );
	CheckError();
	glGenerateMipmap( GL_TEXTURE_2D );
	CheckError();
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	CheckError();
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	CheckError();
	glBindTexture( GL_TEXTURE_2D, 0 );
	CheckError();
}