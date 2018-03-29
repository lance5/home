#pragma once
#include "IUnKnown.h"

class CTexture2D
{
	DEFAULT_METHOD( CTexture2D );

	uint32		m_nTextureID;

public:
	CTexture2D();
	~CTexture2D();

	void		SetTextureData( uint8 nFormat, uint32 nWidth, uint32 nHeight, const byte* pData  );

	uint32		GetTextureID() const { return m_nTextureID; }
};