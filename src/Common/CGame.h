#pragma once

struct GLFWwindow;
class CCamera;
class CScene;
class CGraphics;
class CFrameBuffer;

class CGame;
static CGame* m_sAppInstance;

class CGame
{
private:
	enum eGameState
	{
		eGameState_Active,
		eGameState_Menu,
		eGameState_Win,
	};
	eGameState				m_nState;
	GLFWwindow*				m_pMainWindow;
	int64					m_nLastFrame;
	uint32					m_nFrameInterval;
	TList<CScene>			m_listScene;
	uint32					m_nWindowWidth;
	uint32					m_nWindowHeight;
	CGraphics*				m_pGraphics;
	CFrameBuffer*			m_pMainFrame;

	void					ProcessInput( uint32 nDeltaTime );
	void					Update( uint32 nDeltaTime );
	void					Render();
public:
	CGame( uint32 nWidth, uint32 nHeight, const char* szWindowName, uint32 nFrameInterval );
	virtual ~CGame();

	void					OnKeyCallback( int nKey, int nAction );
	void					OnRun();
	int						OnQuit();

	void					AddScene( CScene* pScene );
	void					RegisterShader( uint32 nShaderID );
	uint32					GetWindowWidth() const { return m_nWindowWidth; }
	uint32					GetWindowHeight() const { return m_nWindowHeight; }
	CGraphics&				GetGraphics() { return *m_pGraphics; }

	static CGame*			Inst() { return m_sAppInstance; }
};

#define CREATE_GAME( nWindowWidth, nWindowHeight, szWindowName, nFrameInterval, ClassGame ) \
	int main( int argc, char* argv[] ) \
	{ \
		m_sAppInstance = new ClassGame( nWindowWidth, nWindowHeight, szWindowName, nFrameInterval ); \
		CGame* game = CGame::Inst(); \
		game->OnRun(); \
		int nResult = game->OnQuit(); \
		SAFE_DELETE( game ); \
		return nResult; \
	}