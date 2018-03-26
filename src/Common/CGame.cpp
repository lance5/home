#include "CommonHelp.h"
#include <map>
#include "CScene.h"
#include "CShader.h"

#include "CGame.h"
#include "glad.h"
#include "glfw/glfw3.h"

#include "CCamera.h"

void OnGlfwKeyCallback( GLFWwindow * pWindow, int nKey, int nScanCode, int nAction, int nMode )
{
	if ( nKey == GLFW_KEY_ESCAPE && nAction == GLFW_PRESS )
		glfwSetWindowShouldClose( pWindow, GL_TRUE );

	CGame::Inst().OnKeyCallback( nKey, nAction );
}

CGame::CGame()
	: m_pMainCamera( new CCamera )
	, m_pGameListen( NULL )
{
}


CGame::~CGame()
{
}

CGame & CGame::Inst()
{
	static CGame s_instance;
	return s_instance;
}

void CGame::Init( uint32 nWidth, uint32 nHeight, char* szWindowName, IGameListen* pGameListen, uint32 nFrameInterval /* = 33 */ )
{
	m_pGameListen = pGameListen;
	m_nFrameInterval = nFrameInterval;
	m_nState = eGameState_Active;
	m_nLastFrame = (int64)( glfwGetTime() * 1000 );
	m_nWindowWidth = nWidth;
	m_nWindownHeight = nHeight;

	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
	m_pMainWindow = glfwCreateWindow( m_nWindowWidth, m_nWindownHeight, szWindowName, nullptr, nullptr );
	glfwMakeContextCurrent( m_pMainWindow );
	glfwSetKeyCallback( m_pMainWindow, OnGlfwKeyCallback );
	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
		Assert( false );
	glViewport( 0, 0, m_nWindowWidth, m_nWindownHeight );
	glEnable( GL_CULL_FACE );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	InitEngineShader();

	m_pGameListen->OnCreated();
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

		glClearColor( 0.0f, 0.0f, 0.0f,1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		Render();

		glfwSwapBuffers( m_pMainWindow );

		uint32 nTheRumTime = (uint32)( (int64)( glfwGetTime() * 1000 ) - nCurrentFrame );
		if ( nTheRumTime <= m_nFrameInterval )
			Sleep( m_nFrameInterval - nTheRumTime );
	}
}

int CGame::OnQuit() 
{
	glfwTerminate();
	m_pGameListen->OnDestroy();
	for ( ShaderMap::iterator it = m_mapShader.begin(); 
		it != m_mapShader.end(); ++it )
		SAFE_DELETE( it->second );
	return 0;
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
	CScene* pScene = m_listScene.GetFirst();
	for ( ; pScene; pScene = pScene->GetNext() )
		pScene->OnRender();
}

void CGame::InitEngineShader()
{
	const char* szShader[eShaderType_ShellStart][eShader_Count] =
	{
		{ 
			"#version 330 core\n"
			"layout (location = 0) in vec4 vertex;\n"
			"out vec2 TexCoords;\n"
			"uniform mat4 model;\n"
			"uniform mat4 projection;\n"
			"void main()\n"
			"{\n"
			"	TexCoords = vertex.zw;\n"
			"	gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
			"}",
			"#version 330 core\n"
			"in vec2 TexCoords;\n"
			"out vec4 color;\n"
			"uniform sampler2D image;\n"
			"uniform vec3 spriteColor;\n"
			"void main()\n"
			"{\n"
			"	color = vec4(spriteColor, 1.0) * texture(image, TexCoords);\n"
			"}",
			nullptr 
		}
	};
	for ( uint32 i = 0; i < eShaderType_ShellStart; ++i )
	{
		m_mapShader[eShaderType_Sprite] = new CShader( szShader[i] );
	}
}
