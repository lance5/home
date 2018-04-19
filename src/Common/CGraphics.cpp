#include "stdafx.h"
#include "CGraphics.h"
#include "CShader.h"
#include "CFrameBuffer.h"
#include "CRenderModel.h"
#include "glad.h"

CGraphics::CGraphics()
	: m_pCurFrameBuffer( nullptr )
{
	memset( m_aryShader, 0, sizeof( m_aryShader ) );
	InitShader();

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays( 1, &m_nTestVAO );
	glGenBuffers( 1, &m_nTestVBO );
	glBindVertexArray( m_nTestVAO );
	glBindBuffer( GL_ARRAY_BUFFER, m_nTestVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );
}

CGraphics::~CGraphics()
{
	glDeleteVertexArrays( 1, &m_nTestVAO );
	glDeleteBuffers( 1, &m_nTestVBO );

	for( uint32 i = 0; i < eShaderType_Count; ++i )
		SAFE_DELETE( m_aryShader[i] );
}

void CGraphics::InitShader()
{
	const char* szShader[eShaderType_Count][eShader_Count] =
	{
		{ 
			"#version 330 core\n"
			"layout (location = 0) in vec3 vertex;\n"
			"layout (location = 1) in vec3 normal;\n"
			"layout (location = 2) in vec2 texCoord;\n"
			"uniform mat4 model;\n"
			"void main()\n"
			"{\n"
				"gl_Position = model * vec4( vertex.x, vertex.y, vertex.z, 1.0 );"
			"}",
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0",
			nullptr 
		},
		{ 
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
				"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\n",
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0",
			nullptr 
		}
	};
	for ( uint32 i = 0; i < eShaderType_Count; ++i )
	{
		m_aryShader[i] = new CShader( szShader[i] );
	}
}

void CGraphics::RenderObject( uint32 nShaderID, const CRenderModel& model, const CMatrix & mat )
{
	if( m_pCurFrameBuffer )
		m_pCurFrameBuffer->BindFrame();

	m_aryShader[nShaderID]->Use();
	m_aryShader[nShaderID]->SetValue( "model", mat );

	for ( uint32 i = 0; i < model.m_vecObject.size(); ++i )
	{
		const CRenderModel::SObject& element = model.m_vecObject[i];
		glBindVertexArray( element.m_nVertexArrays );
		CheckError();
		glDrawArrays( GL_TRIANGLES, 0, element.m_nCount );
		CheckError();
		glBindVertexArray( 0 );
		CheckError();
	}

	if( m_pCurFrameBuffer )
		m_pCurFrameBuffer->UnBindFrame();
}

void CGraphics::RenderTest()
{
	glBindVertexArray( m_nTestVAO );
	CheckError();
	m_aryShader[eShaderType_Test]->Use();
	glDrawArrays( GL_TRIANGLES, 0, 3 );
	CheckError();
	glBindVertexArray( 0 );
	CheckError();
}
