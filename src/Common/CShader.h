#pragma once

enum
{
	eShader_Vertex,
	eShader_Fragment,
	eShader_Geometry,
	eShader_Count,
};

class CShader
{
	uint32 m_nProgramID;

public:
	CShader( const char* szShader[eShader_Count] );
	~CShader();

	void Use();
	template<typename _Type>
	void SetValue( const char* szName, const _Type& Value ) const;
	int32 GetUniformLoca( const char* szName ) const;
};

