#include "stdafx.h"
#include "CGraphics.h"
#include "CShader.h"
#include "CFrameBuffer.h"

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
	Assert( !m_pCurFrameBuffer );
}

void CGraphics::InitShader()
{
	const char* szShader[eShaderType_Count][eShader_Count] =
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
	for ( uint32 i = 0; i < eShaderType_Count; ++i )
	{
		m_aryShader[i] = new CShader( szShader[i] );
	}
}

void CGraphics::RenderObject( uint32 nShaderID, const CRenderModel& model, const CMatrix & mat )
{
	if( m_pCurFrameBuffer )
		m_pCurFrameBuffer->BindFrame();
	
	/* ¿ªÊ¼äÖÈ¾ */


	if( m_pCurFrameBuffer )
		m_pCurFrameBuffer->UnBindFrame();
}

template<class ClassName>
ClassName* CGraphics::CreateResource()
{
	return new ClassName();
}