#pragma once
class CTexture2D;

class CSprite : public CNode2D
{
	CTexture2D*	m_pTexture;
	uint32		m_nWidth;
	uint32		m_nHeight;
public:
	CSprite();
	~CSprite();

	void	SetTexture( const char* pFileName );
};

