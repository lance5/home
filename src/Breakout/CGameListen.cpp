#include "stdafx.h"
#include "CGameListen.h"
#include "Common/CScene.h"
#include "CScene1.h"

CGameListen::CGameListen()
	: m_pScene( new CScene1 )
{
}


CGameListen::~CGameListen()
{
}

void CGameListen::OnCreated()
{
	CGame::Inst().AddScene( m_pScene );

	m_pMainCamera.SetViewProt( 800, 600 );
}

void CGameListen::OnDestroy()
{
	SAFE_DELETE( m_pScene );
}

CREATE_GAME( 800, 600, "Breakout", CGameListen );