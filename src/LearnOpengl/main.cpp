#include "stdafx.h"

GLFWwindow* g_pWindow = nullptr;
CCamera g_MainCamera(glm::vec3(0.0f, 0.0f, 3.0f));
// timing
float g_DeltaTime = 0.0f;	// time between current frame and last frame
float g_LastFrame = 0.0f;

int main( int argc, char* argv[] )
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	g_pWindow = glfwCreateWindow(g_nWindowWidth, g_nWindowHeight, g_szWindowTitle, NULL, NULL);
	Assert(g_pWindow != nullptr);
	glfwMakeContextCurrent(g_pWindow);
	glfwSetFramebufferSizeCallback(g_pWindow, FrameBufferSizeCallback);
	glfwSetCursorPosCallback(g_pWindow, MouseCallback);
	glfwSetScrollCallback(g_pWindow, ScrollCallback);
	glfwSetInputMode(g_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		Assert(false);
	glEnable(GL_DEPTH_TEST);
	int nResultCode = CurMainFunction(argc, argv);
	glfwTerminate();
	return nResultCode;
}

void FrameBufferSizeCallback(GLFWwindow* pWin, int nWidth, int nHeight)
{
	glViewport( 0, 0, nWidth, nHeight );
}

void processInput(GLFWwindow* pWindow)
{
	float fCameraSpeed = 0.05f;
	if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
		g_MainCamera.ProcessKeyboard(FORWARD, g_DeltaTime);
	if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
		g_MainCamera.ProcessKeyboard(BACKWARD, g_DeltaTime);
	if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
		g_MainCamera.ProcessKeyboard(LEFT, g_DeltaTime);
	if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
		g_MainCamera.ProcessKeyboard(RIGHT, g_DeltaTime);
	if (glfwGetKey(pWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
		g_MainCamera.ProcessKeyboard(SPACE, g_DeltaTime);
	if (glfwGetKey(pWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		g_MainCamera.ProcessKeyboard(SHIFT, g_DeltaTime);
	if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, true);
	}
}

void MouseCallback(GLFWwindow* pWindow, double xPos, double yPos)
{
	static double fLastX = 400;
	static double fLastY = 300;
	static bool bOne = true;
	static double fPitch = 0.0f;
	static double fYaw = 0.0f;

	if (bOne)
	{
		bOne = false;
		fLastX = xPos;
		fLastY = yPos;
	}

	double xoffset = xPos - fLastX;
	double yoffset = fLastY - yPos; // reversed since y-coordinates go from bottom to top

	fLastX = xPos;
	fLastY = yPos;

	g_MainCamera.ProcessMouseMovement( (float)xoffset, (float)yoffset );
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	g_MainCamera.ProcessMouseScroll( (float)yoffset );
}

uint32 loadTexture( const char* szPath )
{
	GLuint nTextureID;
	glGenTextures( 1, &nTextureID );
	glBindTexture( GL_TEXTURE_2D, nTextureID );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	uint32 nWidth, nHeight;
	EImageFormat nImgFormat;
	const byte* data = CFileManage::Inst().LoadImg( szPath, nWidth, nHeight, nImgFormat );
	GLenum nFormat;
	switch( nImgFormat )
	{
	case eIF_RED:
		nFormat = GL_RED;
		break;
	case eIF_RGB:
		nFormat = GL_RGB;
		break;
	case eIF_RGBA:
		nFormat = GL_RGBA;
		break;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nWidth, nHeight, 0, nFormat, GL_UNSIGNED_BYTE, (const void*)data);
	glGenerateMipmap(GL_TEXTURE_2D);
	return nTextureID;
}