#include "stdafx.h"
#include <Common/CResourceModel.h>

int main3( int argc, char* argv[] )
{
	CResourceModel ResModel;
	CFileManage::Inst().Load( "nanosuit/nanosuit.obj", ResModel );

	const char szVertex[] = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 vPos;"
		"layout (location = 1) in vec3 vNormal;"
		"layout (location = 2) in vec2 vTexCoords;"
		"void main()"
		"{"
		"gl_Position = vec4( vPos, 1.0 );"
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

	GLuint VAO;
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );

	GLuint VBO[3];
	glGenBuffers( ELEM_COUNT( VBO ), VBO );
	glBindBuffer( GL_ARRAY_BUFFER, VBO[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeof( SModelVertex ) * ResModel.GetModelVertex().size(),
		&ResModel.GetModelVertex()[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( SModelVertex ), (void*)0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( SModelVertex ), (void*)offsetof( SModelVertex, m_aryNoram ) );
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( SModelVertex ), (void*)offsetof( SModelVertex, m_aryTexCoord ) );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );

	const std::vector<SObjectIndex>& vecObject = ResModel.GetModelObject();
	vector<uint32> vecEBO;
	vecEBO.resize( vecObject.size() );
	glGenBuffers( vecEBO.size(), &vecEBO[0] );
	for ( uint32 i = 0; i < vecEBO.size(); ++i )
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vecEBO[i] );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( vecObject[i].m_aryIndex[0] ) * vecObject[i].m_aryIndex.size(),
			&vecObject[i].m_aryIndex[0], GL_STATIC_DRAW );
	}

	lampShader.Use();
	glBindVertexArray( VAO );

	MainWhileStart
		for ( uint32 i = 0; i < vecEBO.size(); ++i )
		{
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vecEBO[i] );
			glDrawElements( GL_TRIANGLES, vecObject[i].m_aryIndex.size(), GL_UNSIGNED_INT, 0 );
		}
	MainWhileEnd
	return 0;
}