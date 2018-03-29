#include "stdafx.h"
#include "CMaterial.h"

CMaterial::CMaterial()
	: m_nRef( 1 )
{
	memset( m_Texture, 0, sizeof( m_Texture ) );
}

CMaterial::~CMaterial()
{
	for ( uint32 i = 0; i < ELEM_COUNT( m_Texture ); ++i )
	{
		if( !m_Texture[i] )
			continue;
		m_Texture[i]->Release();
	}
}

void CMaterial::SetTexture( uint8 nTexture, CTexture2D& p )
{
	p.AddRef();
	m_Texture[nTexture] = &p;
}
