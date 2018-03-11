#include "CommonHelp.h"
#include "CTexture2D.h"

#include "glad.h"

CTexture2D::CTexture2D()
	: m_nTextureID( 0 )
{
	glGenTextures( 1, &m_nTextureID );
}

CTexture2D::~CTexture2D()
{
	glDeleteTextures( 1, &m_nTextureID );
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
	glTexImage2D( GL_TEXTURE_2D, 0, nInternalFormat, nWidth,
		nHeight, 0, nInternalFormat, GL_UNSIGNED_BYTE, pData );
	glGenerateMipmap( GL_TEXTURE_2D );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glBindTexture( GL_TEXTURE_2D, 0 );
}