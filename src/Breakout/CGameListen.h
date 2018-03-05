#pragma once

class CGameListen : public IGameListen
{
	CScene*			m_pScene;

public:
	CGameListen();
	virtual ~CGameListen();

	virtual void	OnCreated();
	virtual void	OnDestroy();
};

