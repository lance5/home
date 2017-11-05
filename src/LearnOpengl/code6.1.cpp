#include "stdafx.h"

void processInput(GLFWwindow* pWindow);
void mouse_callback(GLFWwindow* pWindow, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main1( int nArgv, char* szArgc[] )
{
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

	uint32 nTexture[2];
	GLenum aryType[2] = {
		GL_RGB,
		GL_RGBA,
	};
	for ( uint32 i = 0; i < 2; ++i )
		nTexture[i] = loadTexture( szTexturePath[i].c_str() );

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

	MainWhileStart
		glm::mat4 matView = g_MainCamera.GetViewMatrix();
		glm::mat4 matProjection = g_MainCamera.GetProjection( (float)g_nWindowWidth, (float)g_nWindowHeight );

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
	MainWhileEnd

	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );
	glDeleteBuffers( 1, &EBO );

	return 0;
}