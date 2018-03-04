#include <vector>

#include "TypeDef.h"
#include "CGame.h"

CGame::CGame()
{
}


CGame::~CGame()
{
}

void CGame::Init( uint32 nWidth, uint32 nHeight )
{
	m_vecKeys.reserve( 1024 );

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nState = eGameState_Active;
}

void CGame::PushKey( uint32 nKey )
{
	m_vecKeys.push_back( nKey );
}

void CGame::ProcessInput( int64 nDeltaTime )
{
}

void CGame::Update( int64 nDeltaTime )
{
}

void CGame::Render()
{
}

CGame & CGame::Inst()
{
	static CGame s_instance;
	return s_instance;
}
