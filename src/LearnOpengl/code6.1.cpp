#include "stdafx.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput( GLFWwindow* pWindow );
void mouse_callback(GLFWwindow* pWindow, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const uint32 SCR_WIDTH = 800;
const uint32 SCR_HEIGHT = 600;

CCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main( int nArgv, char* szArgc[] )
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* pWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	Assert(pWindow != nullptr);
	glfwMakeContextCurrent(pWindow);
	glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);
	glfwSetInputMode( pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
	glfwSetCursorPosCallback( pWindow, mouse_callback );
	glfwSetScrollCallback( pWindow, scroll_callback );
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		Assert(false);

	//glEnable( GL_MULTISAMPLE );
	glEnable( GL_DEPTH_TEST );

	const char* szShaderPath[eShader_Count] =
	{
		"6.1.coordinate_systems.vs",
		"6.1.coordinate_systems.fs",
		nullptr,
	};
	CShader shader(szShaderPath);

	float vertices[] = {
		-0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,	1.0f,	0.0f,	1.0f,
		0.5f,	-0.5f,	1.0f,	1.0f,	0.0f,
		0.5f,	0.5f,	1.0f,	1.0f,	1.0f,

		-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,	0.0f,	0.0f,	1.0f,
		-0.5f,	-0.5f,	1.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,	1.0f,	1.0f,	1.0f,
		
		0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,
		0.5f,	0.5f,	0.0f,	0.0f,	1.0f,
		-0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,	0.0f,	1.0f,	1.0f,

		0.5f, -0.5f,	1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,	1.0f,	0.0f,	1.0f,
		0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,	0.0f,	1.0f,	1.0f,

		-0.5f,	0.5f,	1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,	0.0f,	0.0f,	1.0f,
		0.5f,	0.5f,	1.0f,	1.0f,	0.0f,
		0.5f,	0.5f,	0.0f,	1.0f,	1.0f,

		-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,
		-0.5,	-0.5f,	1.0f,	0.0f,	1.0f,
		0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,	1.0f,	1.0f,	1.0f,
	};
	uint32 indices[] = {
		2,	1,	0,
		1,	2,	3,

		6,	5,	4,
		5,	6,	7,

		10,	9,	8,
		9,	10,	11,

		14,	13,	12,
		13,	14,	15,

		18,	17,	16,
		17,	18,	19,

		22,	21,	20,
		21,	22,	23,
	};
	uint32 VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers( 1, &VBO );
	glGenBuffers( 1, &EBO );

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (void*)(3 * sizeof(float)) );
	glEnableVertexAttribArray( 1 );

	string szTexturePath[2] = {
		"./../../res/container.jpg",
		"./../../res/awesomeface.png",
	};

	stbi_set_flip_vertically_on_load( true );
	uint32 nTexture[2];
	GLenum aryType[2] = {
		GL_RGB,
		GL_RGBA,
	};
	for ( uint32 i = 0; i < 2; ++i )
	{
		glGenTextures( 1, &nTexture[i] );
		glBindTexture( GL_TEXTURE_2D, nTexture[i] );

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int32 nWidth, nHeight, nrChannels;
		unsigned char* data = stbi_load(szTexturePath[i].c_str(), &nWidth, &nHeight, &nrChannels, 0);
		Assert(data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nWidth, nHeight, 0, aryType[i], GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}

	shader.Use();
	shader.SetValue( "texture1", 0 );
	shader.SetValue( "texture2", 1 );

	for (uint32 i = 0; i < 2; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, nTexture[i]);
	}

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	while ( !glfwWindowShouldClose( pWindow ) )
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput( pWindow );

		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glm::mat4 matView = camera.GetViewMatrix();
		glm::mat4 matProjection( 1 );
		matProjection = glm::perspective(glm::radians( camera.Zoom ),
			(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f);

		shader.SetValue("view", matView);
		shader.SetValue("projection", matProjection);
		
		glBindVertexArray( VAO );
		for( uint32 i = 0; i < 10; i++ )
		{
			glm::mat4 matModel( 1 );
			matModel = glm::translate( matModel, cubePositions[i] );
			float fAngle = 20.0f * i;
			matModel = glm::rotate( matModel, glm::radians( fAngle ), glm::vec3( 1.0f, 0.3f, 0.5f ) );
			shader.SetValue( "model", matModel );

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}

		glfwSwapBuffers( pWindow );
		glfwPollEvents();
		Sleep( 15 );
	}

	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );
	glDeleteBuffers( 1, &EBO );

	glfwTerminate();
	return 0;
}

void processInput( GLFWwindow* pWindow )
{
	float fCameraSpeed = 0.05f;
	if ( glfwGetKey( pWindow, GLFW_KEY_W ) == GLFW_PRESS )
		camera.ProcessKeyboard( FORWARD, deltaTime );
	if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, true);
	}
}

void mouse_callback( GLFWwindow* pWindow, double xPos, double yPos )
{
	static float fLastX = 400;
	static float fLastY = 300;
	static bool bOne = true;
	static float fPitch = 0.0f;
	static float fYaw = 0.0f;

	if ( bOne )
	{
		bOne = false;
		fLastX = xPos;
		fLastY = yPos;
	}

	float xoffset = xPos - fLastX;
	float yoffset = fLastY - yPos; // reversed since y-coordinates go from bottom to top

	fLastX = xPos;
	fLastY = yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport( 0, 0, width, height );
}

struct MidiMessage
{
	friend std::unique_ptr<MidiMessage>;
	virtual int Send( int hmo ) = 0;
};

struct MidiEvent
{
	std::unique_ptr< MidiMessage > message;

	int Send( int hmo )
	{
		return message->Send( hmo );
	}
};

struct _NativeMidiSong
{
	std::vector<MidiEvent> Events;
};