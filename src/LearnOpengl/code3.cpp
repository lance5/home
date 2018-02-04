#include "stdafx.h"
#include <Common/CResourceModel.h>

int main3( int argc, char* argv[] )
{
	CResourceModel ResModel;
	CFileManage::Inst().Load( "nanosuit/nanosuit.obj", ResModel );

	GLuint VAO;
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );

	GLuint VBO[3];
	glGenBuffers( ELEM_COUNT( VBO ), VBO );

	glBindBuffer( GL_ARRAY_BUFFER, VBO[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * ResModel.GetVertex().size(), &ResModel.GetVertex()[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, VBO[1] );
	glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * ResModel.GetNormal().size(), &ResModel.GetNormal()[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 1 );

	glBindBuffer( GL_ARRAY_BUFFER, VBO[2] );
	glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * ResModel.GetTexCoord().size(), &ResModel.GetTexCoord()[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 2 );

	//const std::vector<SObjectIndex>& ResModel.GetModelObject();

	const char szVertex[] = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 vPos;"
		"layout (location = 1) in vec3 vNormal;"
		"layout (location = 2) in vec2 vTexCoords;"
		"void main()"
		"{"
		"gl_Position = vPos;"
		"}";
	const char szFragment[] = 
		"#version 330 core\n"
		"out vec4 FragColor;"
		"void main()"
		"{"
		"FragColor = vec4( 0.5 );"
		"}";

	const char* szLampPath[eShader_Count] = { szVertex, szFragment, nullptr, };
	CShader lampShader(szLampPath);

	const std::vector<SObjectIndex>& vecObject = ResModel.GetModelObject();

	MainWhileStart
		
	MainWhileEnd
	return 0;
}