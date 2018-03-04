#include "stdafx.h"

void FuncKeyCallback( GLFWwindow* pWindow, int nKey, int nScanCode, int nAction, int nMode );

const uint32 SCREEN_WIDTH = 800;
const uint32 SCREEN_HEIGHT = 600;

int main( int argc, char* argv[] )
{
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	GLFWwindow* pWindow = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr );
	glfwMakeContextCurrent( pWindow );
	glfwSetKeyCallback( pWindow, FuncKeyCallback );

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		Assert(false);

	glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
	glEnable( GL_CULL_FACE );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	CGame::Inst().Init( SCREEN_WIDTH, SCREEN_HEIGHT );

	int64 nLastFrame = (int64)( glfwGetTime() * 1000 );

	while ( !glfwWindowShouldClose( pWindow ) )
	{
		int64 nCurrentFrame = (int64)( glfwGetTime() * 1000 );
		int64 nDeltaTime = nCurrentFrame = nLastFrame;
		nLastFrame = nCurrentFrame;
		glfwPollEvents();

		CGame::Inst().ProcessInput( nDeltaTime );
		CGame::Inst().Update( nDeltaTime );

		glClearColor( 0.0f, 0.0f, 0.0f,1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		CGame::Inst().Render();

		glfwSwapBuffers( pWindow );
	}

	glfwTerminate();
	return 0;
}

void FuncKeyCallback( GLFWwindow* pWindow, int nKey, int nScanCode, int nAction, int nMode )
{
	if ( nKey == GLFW_KEY_ESCAPE && nAction == GLFW_PRESS )
		glfwSetWindowShouldClose( pWindow, GL_TRUE );
	
	if ( nAction == GLFW_PRESS && nKey >= 0 )
		CGame::Inst().PushKey( nKey );
}