#include "CommonHelp.h"
#include "TVector3.h"
#include "CFileManage.h"

#include "CResourceModel.h"
#include "glfw/glfw3.h"

CResourceModel::CResourceModel()
{
}

CResourceModel::~CResourceModel()
{
}

void CResourceModel::OnFileLoaded( const char* szFileName, const byte * szBuffer, const uint32 nSize )
{
	m_vecModelVertex.reserve( 65535 );

	std::vector<float> vecVertex( 65535 );
	std::vector<float> vecTexCoord( 65535 );
	std::vector<float> vecNormal( 65535 );

	uint32 nCurPos = 0;
	std::vector<cstring> vecParam;
	for( uint32 i = 0; i < nSize; ++i )
	{
		if( szBuffer[i] != '\n' )
			continue;

		const char* szString = (const char*)( szBuffer + nCurPos );
		uint32 nCurSize = i - nCurPos;
		nCurPos = i + 1;
		if( szString[nCurSize - 1] == '\r' )
			--nCurSize;
		cstring sString( szString, nCurSize );

		if( nCurSize == 0 )
			continue;

		vecParam.clear();
		partition( sString, ' ', vecParam );

		if ( !strncmp( vecParam[0].c_str(), "#", vecParam[0].size() ) )
			continue;
		else if ( !strncmp( vecParam[0].c_str(), "v", vecParam[0].size() ) )
		{
			Assert( vecParam.size() == 4 );
			vecVertex.push_back( (float)atof( vecParam[1].c_str() ) );
			vecVertex.push_back( (float)atof( vecParam[2].c_str() ) );
			vecVertex.push_back( (float)atof( vecParam[3].c_str() ) );
		}
		else if ( !strncmp( vecParam[0].c_str(), "vt", vecParam[0].size() ) )
		{
			Assert( vecParam.size() == 3 );
			vecTexCoord.push_back( (float)atof( vecParam[1].c_str() ) );
			vecTexCoord.push_back( (float)atof( vecParam[2].c_str() ) );
		}
		else if ( !strncmp( vecParam[0].c_str(), "vn", vecParam[0].size() ) )
		{
			Assert( vecParam.size() == 4 );
			vecNormal.push_back( (float)atof( vecParam[1].c_str() ) );
			vecNormal.push_back( (float)atof( vecParam[2].c_str() ) );
			vecNormal.push_back( (float)atof( vecParam[3].c_str() ) );
		}
		else if ( !strncmp( vecParam[0].c_str(), "mtllib", vecParam[0].size() ) )
		{
			Assert( vecParam.size() == 2 );
			std::string strMtlFile( vecParam[1].c_str(), vecParam[1].size() );
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
		else if ( !strncmp( vecParam[0].c_str(), "o", vecParam[0].size() ) )
		{
			Assert( vecParam.size() == 2 );
			SObjectIndex sIndex;
			sIndex.m_strName = string( vecParam[1].c_str(), vecParam[1].size() );
			m_vecObject.push_back( sIndex );
		}
		else if ( !strncmp( vecParam[0].c_str(), "usemtl", vecParam[0].size() ) )
		{
			Assert( vecParam.size() == 2 );
			string szName( vecParam[1].c_str(), vecParam[1].size() );
			Assert( m_mapMaterial.find( szName ) != m_mapMaterial.end() );
			m_vecObject.rbegin()->m_pMaterial = &m_mapMaterial[szName];
		}
		else if ( !strncmp( vecParam[0].c_str(), "s", vecParam[0].size() ) )
		{
			Assert( vecParam.size() == 2 );
			if( !strcmp( vecParam[1].c_str(), "1" ) || !strcmp( vecParam[1].c_str(), "on" ) )
				m_vecObject.rbegin()->m_bSmooth = true;
			else
				m_vecObject.rbegin()->m_bSmooth = false;
		}
		else if ( !strncmp( vecParam[0].c_str(), "f", vecParam[0].size() ) )
		{
			Assert( vecParam.size() >= 2 );
			vector<cstring> aryIndex;
			aryIndex.reserve( 3 );
			auto it = vecParam.begin();
			for ( ++it; it != vecParam.end(); ++it )
			{
				aryIndex.clear();
				partition( *it, '/', aryIndex );
				Assert( aryIndex.size() == 3 );
				m_vecObject.rbegin()->m_aryIndex.push_back( m_vecModelVertex.size() );
				uint32 nVectexIndex = (uint32)atol( aryIndex[0].c_str() );
				uint32 nTexCoordIndex = (uint32)atol( aryIndex[1].c_str() );
				uint32 nNoramIndex =  (uint32)atol( aryIndex[2].c_str() );
				SModelVertex modelVertex;
				memcpy( modelVertex.m_aryVertex, &vecVertex[nVectexIndex*3], sizeof( modelVertex.m_aryVertex ) );
				memcpy( modelVertex.m_aryNoram, &vecVertex[nNoramIndex*3], sizeof( modelVertex.m_aryNoram ) );
				memcpy( modelVertex.m_aryTexCoord, &vecVertex[nVectexIndex*2], sizeof( modelVertex.m_aryTexCoord ) );
				m_vecModelVertex.push_back( modelVertex );
			}
		}
		else
			Log << "Obj FIle Read Not Realize Keyword : \"" << string( sString.c_str(), sString.size() ) << "\"" << endl;
	}
}

void CResourceModel::OnLoadMtllib( const char* szFileName, const byte* szBuffer, const uint32 nSize )
{
	uint32 nCurPos = 0;
	vector<cstring> vecParam;
	for( uint32 i = 0; i < nSize; ++i )
	{
		if( szBuffer[i] != '\n' )
			continue;

		const char* szString = (const char*)( szBuffer + nCurPos );
		uint32 nCurSize = i - nCurPos;
		nCurPos = i + 1;
		if( szString[nCurSize - 1] == '\r' )
			--nCurSize;
		cstring sString( szString, nCurSize );

		if( nCurSize == 0 )
			continue;

		vecParam.clear();
		partition( sString, ' ', vecParam );

		if ( !strncmp( vecParam[0].c_str(), "#", vecParam[0].size() ) )
			continue;
		else if ( !strncmp( vecParam[0].c_str(), "newmtl", vecParam[0].size() ) )
			m_mapMaterial[string( vecParam[1].c_str(), vecParam[1].size() ) ];
		else if ( !strncmp( vecParam[0].c_str(), "Ns", vecParam[0].size() ) )
			m_mapMaterial.rbegin()->second.m_fShininess = (float)atof( vecParam[1].c_str() );
		else if ( !strncmp( vecParam[0].c_str(), "Ka", vecParam[0].size() ) )
		{
			CVector3f& vector = m_mapMaterial.rbegin()->second.m_vec3Ambient;
			vector.x = (float)atof( vecParam[1].c_str() );
			vector.y = (float)atof( vecParam[2].c_str() );
			vector.z = (float)atof( vecParam[3].c_str() );
		}
		else if ( !strncmp( vecParam[0].c_str(), "Kd", vecParam[0].size() ) )
		{
			CVector3f& vector = m_mapMaterial.rbegin()->second.m_vec3Diffuse;
			vector.x = (float)atof( vecParam[1].c_str() );
			vector.y = (float)atof( vecParam[2].c_str() );
			vector.z = (float)atof( vecParam[3].c_str() );
		}
		else if ( !strncmp( vecParam[0].c_str(), "Ks", vecParam[0].size() ) )
		{
			CVector3f& vector = m_mapMaterial.rbegin()->second.m_vec3Specular;
			vector.x = (float)atof( vecParam[1].c_str() );
			vector.y = (float)atof( vecParam[2].c_str() );
			vector.z = (float)atof( vecParam[3].c_str() );
		}
		else if ( !strncmp( vecParam[0].c_str(), "Ni", vecParam[0].size() ) )
			m_mapMaterial.rbegin()->second.m_fRefractiveIndex = (float)atof( vecParam[1].c_str() );
		else if ( !strncmp( vecParam[0].c_str(), "d", vecParam[0].size() ) )
			m_mapMaterial.rbegin()->second.m_fFadeOut = (float)atof( vecParam[1].c_str() );
		else if ( !strncmp( vecParam[0].c_str(), "illum", vecParam[0].size() ) )
			m_mapMaterial.rbegin()->second.m_nIllum = atoi( vecParam[1].c_str() );
		else if ( !strncmp( vecParam[0].c_str(), "map_Kd", vecParam[0].size() ) )
			m_mapMaterial.rbegin()->second.m_strDiffuse = string( vecParam[1].c_str(), vecParam[1].size() );
		else if ( !strncmp( vecParam[0].c_str(), "map_Bump", vecParam[0].size() ) )
			m_mapMaterial.rbegin()->second.m_strBump = string( vecParam[1].c_str(), vecParam[1].size() );
		else if ( !strncmp( vecParam[0].c_str(), "map_Ks", vecParam[0].size() ) )
			m_mapMaterial.rbegin()->second.m_strSpecular = string( vecParam[1].c_str(), vecParam[1].size() );
	}
}

const SMaterial& CResourceModel::GetMaterial( const char* szString )
{
	map<string, SMaterial>::iterator it = m_mapMaterial.find( szString );
	Assert( it != m_mapMaterial.end() );
	return it->second;
}