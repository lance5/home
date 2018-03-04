#include "CommonHelp.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TVector4.h"
#include "TMatrix2.h"
#include "TMatrix3.h"
#include "TMatrix4.h"

#include "CShader.h"
#include "glad.h"
#include <glfw\glfw3.h>

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
		glCompileShader( aryShaderID[i] );

		GLint nSuccess;
		glGetShaderiv( aryShaderID[i], GL_COMPILE_STATUS, &nSuccess );
		if( nSuccess )
		{
			glAttachShader(m_nProgramID, aryShaderID[i]);
			continue;
		}

		glGetShaderInfoLog( aryShaderID[i], 1024, nullptr, szBuffer );

		ErrLog << "SHADER_COMPILATION_ERROR of type : " 
			<< aryShaderType[i] << "\n\t" << szBuffer
			<< "\n -- --------------------------------------------------- -- " << std::endl;
	}

	glLinkProgram( m_nProgramID );

	GLint nSuccess;
	glGetProgramiv( m_nProgramID, GL_LINK_STATUS, &nSuccess );
	if (!nSuccess)
	{
		glGetProgramInfoLog( m_nProgramID, 1024, nullptr, szBuffer );
		ErrLog << "PROGRAM_LINKING_ERROR of type : " << szBuffer
		<< "\n -- --------------------------------------------------- -- " << std::endl;
	}

	for ( uint8 i = 0; i < eShader_Count; ++i )
	{
		if (!szShader[i])
			continue;
		glDeleteShader( aryShaderID[i] );
	}
}

CShader::~CShader()
{
	glDeleteProgram( m_nProgramID );
}

void CShader::Use()
{
	glUseProgram( m_nProgramID );
}

int32 CShader::GetUniformLoca(const char* szName) const
{
	return glGetUniformLocation(m_nProgramID, szName);
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
}

template<>
void CShader::SetValue(const char* szName, const int32& nValue) const
{
	glUniform1i( GetUniformLoca( szName), nValue );
}

template<>
void CShader::SetValue(const char* szName, const float& fValue) const
{
	glUniform1f( GetUniformLoca( szName ), fValue );
}

template<>
void CShader::SetValue( const char* szName, const CVector2f& vec ) const
{
	glUniform2fv( GetUniformLoca( szName ), 1, &vec[0] );
}

template<>
void CShader::SetValue(const char* szName, const CVector3f& vec) const
{
	glUniform3fv(GetUniformLoca(szName), 1, &vec[0]);
}

template<>
void CShader::SetValue(const char* szName, const CVector4f& vec ) const
{
	glUniform4fv(GetUniformLoca(szName), 1, &vec[0]);
}

template<>
void CShader::SetValue(const char* szName, const CMatrix2f& mat) const
{
	glUniformMatrix2fv(GetUniformLoca(szName), 1, GL_FALSE, &mat[0][0]);
}

template<>
void CShader::SetValue(const char* szName, const CMatrix3f& mat) const
{
	glUniformMatrix3fv(GetUniformLoca(szName), 1, GL_FALSE, &mat[0][0]);
}

template<>
void CShader::SetValue(const char* szName, const CMatrix4f& mat) const
{
	glUniformMatrix4fv(GetUniformLoca(szName), 1, GL_FALSE, &mat[0][0]);
}