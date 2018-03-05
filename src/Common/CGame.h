#pragma once

struct GLFWwindow;
class CCamera;
class CScene;

class IGameListen
{
public:
	virtual ~IGameListen() {}
	virtual void OnCreated() = 0;
	virtual void OnDestroy() = 0;
};

class CGame
{
	enum eGameState
	{
		eGameState_Active,
		eGameState_Menu,
		eGameState_Win,
	};
	eGameState			m_nState;
	GLFWwindow*			m_pMainWindow;
	IGameListen*		m_pGameListen;
	int64				m_nLastFrame;
	uint32				m_nFrameInterval;
	CCamera*			m_pMainCamera;
	TList<CScene>		m_listScene;

	void				ProcessInput( uint32 nDeltaTime );
	void				Update( uint32 nDeltaTime );
	void				Render();

	CGame();
	~CGame();
public:

	void				OnKeyCallback( int nKey, int nAction );
	void				Init( uint32 nWidth, uint32 nHeight, char* szWindowName, IGameListen* pGameListen, uint32 nFrameInterval = 33 );
	void				OnRun();
	int					OnQuit();

	void				AddScene( CScene* pScene );

	static CGame&		Inst();
};

#define CREATE_GAME( nWindowWidth, nWindowHeight, szWindowName, ClassGameListen ) \
	int main( int argc, char* argv[] ) \
	{ \
		CGame& game = CGame::Inst(); \
		IGameListen* pGameListen = new ClassGameListen; \
		game.Init( nWindowWidth, nWindowHeight, szWindowName, pGameListen ); \
		game.OnRun(); \
		int nResult = game.OnQuit(); \
		SAFE_DELETE(  pGameListen ); \
		return nResult; \
	}