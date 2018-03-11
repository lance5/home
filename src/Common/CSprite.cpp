#include "CommonHelp.h"
#include "CNode.h"
#include "CNode2D.h"
#include "CSprite.h"
#include "CTexture2D.h"

CSprite::CSprite()
	: m_pTexture( new CTexture2D )
	, m_nWidth( 0 )
	, m_nHeight( 0 )
{
}


CSprite::~CSprite()
{
	SAFE_DELETE( m_pTexture );
}

void CSprite::SetTexture( const char * pFileName )
{
	CFileManage::Inst().Load( pFileName, *m_pTexture );
}
