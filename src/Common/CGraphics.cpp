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
}

CGraphics::~CGraphics()
{
	for( uint32 i = 0; i < eShaderType_Count; ++i )
		SAFE_DELETE( m_aryShader[i] );
}

void CGraphics::InitShader()
{
	const char* szShader[eShaderType_Count][eShader_Count] =
	{
		{ 
			"#version 330 core\n"
			"layout (location = 0) in vec4 vertex;\n"
			//"out vec2 TexCoords;\n"
			//"uniform mat4 model;\n"
			//"uniform mat4 projection;\n"
			"void main()\n"
			"{\n"
			//"	TexCoords = vertex.zw;\n"
			//"	gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
				"gl_Position = vertex;"
			"}",
			"#version 330 core\n"
			//"in vec2 TexCoords;\n"
			"out vec4 color;\n"
			//"uniform sampler2D image;\n"
			//"uniform vec3 spriteColor;\n"
			"void main()\n"
			"{\n"
			//"	color = vec4(spriteColor, 1.0) * texture(image, TexCoords);\n"
			"	color = vec4( 0.0 );"
			"}",
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

	m_aryShader[eShaderType_Sprite]->Use();
	
	/* ¿ªÊ¼äÖÈ¾ */
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
