#include "CResourceModel.h"
#include "common.h"
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

	uint32 nCurPos = 0;
	while( nCurPos < nSize )
	{
		// 读取行  
		string strLine;
		for( ; szBuffer[nCurPos] != '\n' && nCurPos < nSize; ++nCurPos )
		{
			strLine.push_back( szBuffer[nCurPos] );
		}
		++nCurPos;

		if( strLine[strLine.size() - 1] == '\r' )
		{
			strLine = strLine.substr( 0, strLine.size() - 1 );
		}

		if( !strLine.size() )
			continue;

		// 防止最后一个参数读取不到  
		strLine.push_back( ' ' );

		vector<string> vecParam;
		string strCurParam;
		for( uint32 i = 0; i < strLine.size(); ++i )
		{
			if ( strLine[i] == ' ' )
			{
				if( strCurParam.size() )
				{
					vecParam.push_back( strCurParam );
					strCurParam.clear();
				}
				continue;
			}

			strCurParam.push_back( strLine[i] );
		}

		string strType = vecParam[0];
		vecParam.erase( vecParam.begin() );
		stringToLower( &strType[0], strType.size() );
		if( !strcmp( strType.c_str(), "v" ) )
		{
			vec3 vVertex;
			vVertex.x = (float)atof( vecParam[0].c_str() );
			vVertex.y = (float)atof( vecParam[1].c_str() );
			vVertex.z = (float)atof( vecParam[2].c_str() );
			vecVertex.push_back( vVertex );
		}
		else if( !strcmp( strType.c_str(), "vt" ) )
		{
			vec2 vVertex;
			vVertex.x = (float)atof( vecParam[0].c_str() );
			vVertex.y = (float)atof( vecParam[1].c_str() );
			vecTexCoord.push_back( vVertex );
		}
		else if( !strcmp( strType.c_str(), "vn" ) )
		{
			vec3 vVertex;
			vVertex.x = (float)atof( vecParam[0].c_str() );
			vVertex.y = (float)atof( vecParam[1].c_str() );
			vVertex.z = (float)atof( vecParam[2].c_str() );
			vecNormal.push_back( vVertex );
		}
		else if( !strcmp( strType.c_str(), "mtllib" ) )
		{
			string strMtlFile = vecParam[0];
			if( !CFileManage::Inst().FileIsExist( strMtlFile.c_str() ) )
			{
				strMtlFile = CFileManage::GetFileDir( szFileName ) + strMtlFile;
				if( !CFileManage::Inst().FileIsExist( strMtlFile.c_str() ) )
					return;
			}

			CFileManage::Inst().Load( strMtlFile.c_str(), );
		}
		else if ( !strcmp(strType.c_str(), "#") )
		{
			continue;
		}
		else
		{
			Log << "Obj FIle Read Not Realize Keyword : \"" << strLine.c_str() << "\"" << endl;
		}
	}

	m_bIsWholeModel = true;
}
