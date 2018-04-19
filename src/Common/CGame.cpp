#include "stdafx.h"
#include "CScene.h"
#include "CShader.h"

#include <map>
#include "CGame.h"
#include "glad.h"
#include "glfw/glfw3.h"

#include "CCamera.h"
#include "CGraphics.h"
#include "CFrameBuffer.h"

void OnGlfwKeyCallback( GLFWwindow * pWindow, int nKey, int nScanCode, int nAction, int nMode )
{
	if ( nKey == GLFW_KEY_ESCAPE && nAction == GLFW_PRESS )
		glfwSetWindowShouldClose( pWindow, GL_TRUE );

	CGame::Inst()->OnKeyCallback( nKey, nAction );
}

CGame::CGame( uint32 nWidth, uint32 nHeight, const char* szWindowName, uint32 nFrameInterval )
	: m_pGraphics( nullptr )
	, m_pMainFrame( nullptr )
{
	m_nFrameInterval = nFrameInterval;
	m_nState = eGameState_Active;
	m_nLastFrame = (int64)( glfwGetTime() * 1000 );
	m_nWindowWidth = nWidth;
	m_nWindowHeight = nHeight;

	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
	m_pMainWindow = glfwCreateWindow( m_nWindowWidth, m_nWindowHeight, szWindowName, nullptr, nullptr );
	glfwMakeContextCurrent( m_pMainWindow );
	glfwSetKeyCallback( m_pMainWindow, OnGlfwKeyCallback );
	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
		Assert( false );
	glViewport( 0, 0, m_nWindowWidth, m_nWindowHeight );
	CheckError();
	glEnable( GL_CULL_FACE );
	CheckError();
	glEnable( GL_BLEND );
	CheckError();
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	CheckError();

	m_pGraphics = new CGraphics();
	m_pMainFrame = new CFrameBuffer( m_nWindowWidth, m_nWindowHeight );
}

CGame::~CGame()
{
	SAFE_DELETE( m_pGraphics );
	glfwTerminate();
}

void CGame::OnCreated()
{
}

void CGame::OnDestroy() 
{
}

void CGame::OnRun()
{
	while ( !glfwWindowShouldClose( m_pMainWindow ) )
	{
		int64 nCurrentFrame = (int64)( glfwGetTime() * 1000 );
		Assert( nCurrentFrame > m_nLastFrame );
		uint32 nDeltaTime = (uint32)( nCurrentFrame - m_nLastFrame );
		m_nLastFrame = nCurrentFrame;
		glfwPollEvents();

		ProcessInput( nDeltaTime );
		Update( nDeltaTime );
		Render();

		glfwSwapBuffers( m_pMainWindow );

		uint32 nTheRumTime = (uint32)( (int64)( glfwGetTime() * 1000 ) - nCurrentFrame );
		if ( nTheRumTime <= m_nFrameInterval )
			Sleep( m_nFrameInterval - nTheRumTime );
	}
}

void CGame::AddScene( CScene* pScene )
{
	m_listScene.Insert( *pScene );
}

void CGame::RegisterShader(uint32 nShaderID)
{
}

void CGame::OnKeyCallback( int nKey, int nAction )
{
}

void CGame::ProcessInput( uint32 nDeltaTime )
{
}

void CGame::Update( uint32 nDeltaTime )
{
	CScene* pScene = m_listScene.GetFirst();
	for ( ; pScene; pScene = pScene->GetNext() )
		pScene->OnUpdate( nDeltaTime );
}

void CGame::Render()
{
	/* ÇåÀíÖ÷»º´æ */
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	CheckError();
	glClearColor( 0.2f, 0.3f, 0.3f, 1.0f ); 
	CheckError();
	glClear( GL_COLOR_BUFFER_BIT );
	CheckError();

	CScene* pScene = m_listScene.GetFirst();
	for ( ; pScene; pScene = pScene->GetNext() )
		pScene->OnRender( m_pGraphics );
}
