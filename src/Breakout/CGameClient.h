#pragma once

class CGameClient : public CGame
{
	CScene*			m_pScene;

public:
	CGameClient( uint32 nWidth, uint32 nHeight, const char* szWindowName, uint32 nFrameInterval );
	virtual ~CGameClient();

	virtual void	OnCreated();
	virtual void	OnDestroy();
};

