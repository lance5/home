#include "stdafx.h"
#include "CommonHelp.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TVector4.h"
#include "CMatrix.h"

#include "CShader.h"
#include "glad.h"
#include <glfw\glfw3.h>
#include "CGraphics.h"

CShader::CShader( const char* szShader[eShader_Count] )
	: m_nProgramID( glCreateProgram() )
{
	GLenum aryShaderType[eShader_Count];
	aryShaderType[eShader_Vertex] = GL_VERTEX_SHADER;
	aryShaderType[eShader_Fragment] = GL_FRAGMENT_SHADER;
	aryShaderType[eShader_Geometry] = GL_GEOMETRY_SHADER;

	uint32 aryShaderID[eShader_Count];
	char szBuffer[1024];

	for ( uint8 i = 0; i < eShader_Count; ++i )
	{
		if ( !szShader[i] )
			continue;

		aryShaderID[i] = glCreateShader( aryShaderType[i] );
		glShaderSource( aryShaderID[i], 1, &szShader[i], nullptr );
		CheckError();
		glCompileShader( aryShaderID[i] );
		CheckError();

		GLint nSuccess;
		glGetShaderiv( aryShaderID[i], GL_COMPILE_STATUS, &nSuccess );
		CheckError();
		if( nSuccess )
		{
			glAttachShader(m_nProgramID, aryShaderID[i]);
			CheckError();
			continue;
		}

		glGetShaderInfoLog( aryShaderID[i], 1024, nullptr, szBuffer );
		CheckError();

		ErrLog << "SHADER_COMPILATION_ERROR of type : " 
			<< aryShaderType[i] << "\n\t" << szBuffer
			<< "\n -- --------------------------------------------------- -- " << std::endl;
	}

	glLinkProgram( m_nProgramID );
	CheckError();

	GLint nSuccess;
	glGetProgramiv( m_nProgramID, GL_LINK_STATUS, &nSuccess );
	CheckError();
	if (!nSuccess)
	{
		glGetProgramInfoLog( m_nProgramID, 1024, nullptr, szBuffer );
		CheckError();
		ErrLog << "PROGRAM_LINKING_ERROR of type : " << szBuffer
		<< "\n -- --------------------------------------------------- -- " << std::endl;
	}

	for ( uint8 i = 0; i < eShader_Count; ++i )
	{
		if (!szShader[i])
			continue;
		glDeleteShader( aryShaderID[i] );
		CheckError();
	}
}

CShader::~CShader()
{
	glDeleteProgram( m_nProgramID );
	CheckError();
}

void CShader::Use()
{
	glUseProgram( m_nProgramID );
	CheckError();
}

int32 CShader::GetUniformLoca(const char* szName) const
{
	return glGetUniformLocation(m_nProgramID, szName);
	CheckError();
}

template<typename _Type>
void CShader::SetValue(const char* szName, const _Type& Value) const
{
	Throw( "no define set!!!" );
}

template<>
void CShader::SetValue(const char* szName, const bool& bValue) const
{
	int32 nValue = bValue ? 1 : 0;
	glUniform1i( GetUniformLoca( szName ), nValue );
	CheckError();
}

template<>
void CShader::SetValue(const char* szName, const int32& nValue) const
{
	glUniform1i( GetUniformLoca( szName), nValue );
	CheckError();
}

template<>
void CShader::SetValue(const char* szName, const float& fValue) const
{
	glUniform1f( GetUniformLoca( szName ), fValue );
	CheckError();
}

template<>
void CShader::SetValue( const char* szName, const CVector2f& vec ) const
{
	glUniform2fv( GetUniformLoca( szName ), 1, &vec[0] );
	CheckError();
}

template<>
void CShader::SetValue(const char* szName, const CVector3f& vec) const
{
	glUniform3fv(GetUniformLoca(szName), 1, &vec[0]);
	CheckError();
}

template<>
void CShader::SetValue(const char* szName, const CVector4f& vec ) const
{
	glUniform4fv(GetUniformLoca(szName), 1, &vec[0]);
	CheckError();
}

template<>
void CShader::SetValue(const char* szName, const CMatrix& mat) const
{
	glUniformMatrix4fv(GetUniformLoca(szName), 1, GL_FALSE, &mat[0][0]);
	CheckError();
}