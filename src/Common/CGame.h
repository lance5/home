#pragma once

enum eGameState
{
	eGameState_Active,
	eGameState_Menu,
	eGameState_Win,
};

class CGame
{
	eGameState			m_nState;
	std::vector<uint32>	m_vecKeys;
	uint32				m_nWidth;
	uint32				m_nHeight;

	CGame();
	~CGame();
public:
	void				Init( uint32 nWidth, uint32 nHeight );
	void				PushKey( uint32 nKey );
	void				ProcessInput( int64 nDeltaTime );
	void				Update( int64 nDeltaTime );
	void				Render();

	static CGame&		Inst();
};
