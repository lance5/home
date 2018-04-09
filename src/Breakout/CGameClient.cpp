#include "stdafx.h"
#include "CGameClient.h"
#include "Common/CScene.h"
#include "CScene1.h"

CREATE_GAME( 800, 600, "Breakout", 33, CGameClient );

CGameClient::CGameClient( uint32 nWidth, uint32 nHeight, const char* szWindowName, uint32 nFrameInterval )
	: CGame( nWidth, nHeight, szWindowName, nFrameInterval )
	, m_pScene( new CScene1 )
{
}


CGameClient::~CGameClient()
{
}

void CGameClient::OnCreated()
{
	AddScene( m_pScene );
}

void CGameClient::OnDestroy()
{
	SAFE_DELETE( m_pScene );
}