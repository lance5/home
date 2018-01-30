#include "stdafx.h"
#include "CResourceModel.h"
#include <glfw/glfw3.h>

using namespace glm;

CResourceModel::CResourceModel()
	: m_bIsWholeModel( false )
{
}

CResourceModel::~CResourceModel()
{
}

void CResourceModel::OnFileLoaded( const char* szFileName, const byte * szBuffer, const uint32 nSize )
{
	m_bIsWholeModel = false;

	vector<vec3> vecVertex;
	vector<vec3> vecNormal;
	vector<vec2> vecTexCoord;
	vector<string> vecParam;

	CStringBuf Buf( (char*)szBuffer, nSize );
	char szLine[2048];
	while ( Buf.ReadLine( szLine, ELEM_COUNT( szLine ) ) )
	{
		vecParam.clear();
		partition( szLine, ' ', vecParam );
		const char* szType = vecParam[0].c_str();
		if ( !strcmp( szType, "#" ) )
			continue;
		else if( !strcmp( szType, "v" ) )
		{
			vec3 vVertex;
			vVertex.x = (float)atof( vecParam[1].c_str() );
			vVertex.y = (float)atof( vecParam[2].c_str() );
			vVertex.z = (float)atof( vecParam[3].c_str() );
			vecVertex.push_back( vVertex );
		}
		else if( !strcmp( szType, "vt" ) )
		{
			vec2 vVertex;
			vVertex.x = (float)atof( vecParam[1].c_str() );
			vVertex.y = (float)atof( vecParam[2].c_str() );
			vecTexCoord.push_back( vVertex );
		}
		else if( !strcmp( szType, "vn" ) )
		{
			vec3 vVertex;
			vVertex.x = (float)atof( vecParam[1].c_str() );
			vVertex.y = (float)atof( vecParam[2].c_str() );
			vVertex.z = (float)atof( vecParam[3].c_str() );
			vecNormal.push_back( vVertex );
		}
		else if( !strcmp( szType, "mtllib" ) )
		{
			string strMtlFile = vecParam[1];
			if( !CFileManage::Inst().FileIsExist( strMtlFile.c_str() ) )
			{
				strMtlFile = CFileManage::GetFileDir( szFileName ) + strMtlFile;
				if( !CFileManage::Inst().FileIsExist( strMtlFile.c_str() ) )
					continue;
			}
			
			const SFileStruct* pFile = CFileManage::Inst().Load( strMtlFile.c_str() );
			Assert( pFile );
			OnLoadMtllib( pFile->m_strFileName.c_str(), pFile->m_pBuffer, pFile->m_nSize );
		}
		else
			Log << "Obj FIle Read Not Realize Keyword : \"" << szLine << "\"" << endl;
	}

	m_bIsWholeModel = true;
}

void CResourceModel::OnLoadMtllib( const char* szFileName, const byte* szBuffer, const uint32 nSize )
{
	vector<string> vecParam;
	CStringBuf Buf( (char*)szBuffer, nSize );
	char szLine[2048];
	while ( Buf.ReadLine( szLine, ELEM_COUNT( szLine ) ) )
	{
		vecParam.clear();
		partition( szLine, ' ', vecParam );
		const char* szType = vecParam[0].c_str();
		if ( !strcmp( szType, "#" ) )
			continue;
		else
			Log << "Obj FIle Read Not Realize Keyword : \"" << szLine << "\"" << endl;
	}
}