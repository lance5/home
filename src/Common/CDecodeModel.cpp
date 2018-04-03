#include "stdafx.h"
#include "TVector3.h"
#include "CFileManage.h"

#include "CDecodeModel.h"
#include "CResourceImg.h"
#include "CGame.h"
#include "CGraphics.h"
#include "CRenderModel.h"

CDecodeModel::CDecodeModel()
{
}

CDecodeModel::~CDecodeModel()
{
	for( uint32 i = 0; i < m_vecObject.size(); ++i )
	{
		SAFE_RELEASE( m_vecObject[i].m_Material );
	}
}

void CDecodeModel::FillRenderModel( CRenderModel& model )
{
	model.SetVertexBuffer( CRenderModel::eBufferType_Vertex, &m_vecVertex[0], m_vecVertex.size() );
	model.SetVertexBuffer( CRenderModel::eBufferType_Normal, &m_vecNormal[0], m_vecNormal.size() );
	model.SetVertexBuffer( CRenderModel::eBufferType_TexCoord, &m_vecTexCoord[0], m_vecTexCoord.size() );

	for( uint32 i = 0; i < m_vecObject.size(); ++i )
	{
		const uint32* aryData[] =
		{
			&m_vecObject[i].m_vecVertexIndex[0],
			&m_vecObject[i].m_vecNoramIndex[0],
			&m_vecObject[i].m_vecTexCoordIndex[0],
		};
		const uint32 arySize[] =
		{
			m_vecObject[i].m_vecVertexIndex.size(),
			m_vecObject[i].m_vecNoramIndex.size(),
			m_vecObject[i].m_vecTexCoordIndex.size(),
		};
		model.PushObjectData( aryData, arySize, m_vecObject[i].m_Material, m_vecObject[i].m_bSmooth );
	}
}

void CDecodeModel::OnFileLoaded( const char* szFileName, const byte * szBuffer, const uint32 nSize )
{
	std::map<std::string, CMaterial*> mapMaterial;
	m_vecVertex.reserve( 65535 );
	m_vecTexCoord.reserve( 65535 );
	m_vecNormal.reserve( 65535 );

	uint32 nCurPos = 0;
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

		cstring aryParam[10];
		uint32 nParamSize = partition( sString, ' ', aryParam );
		if( nParamSize == 0 )
			continue;

		if ( !strncmp( aryParam[0].c_str(), "#", aryParam[0].size() ) )
			continue;
		else if ( !strncmp( aryParam[0].c_str(), "v", aryParam[0].size() ) )
		{
			Assert( nParamSize == 4 );
			m_vecVertex.push_back( (float)atof( aryParam[1].c_str() ) );
			m_vecVertex.push_back( (float)atof( aryParam[2].c_str() ) );
			m_vecVertex.push_back( (float)atof( aryParam[3].c_str() ) );
		}
		else if ( !strncmp( aryParam[0].c_str(), "vt", aryParam[0].size() ) )
		{
			Assert( nParamSize == 3 );
			m_vecTexCoord.push_back( (float)atof( aryParam[1].c_str() ) );
			m_vecTexCoord.push_back( (float)atof( aryParam[2].c_str() ) );
		}
		else if ( !strncmp( aryParam[0].c_str(), "vn", aryParam[0].size() ) )
		{
			Assert( nParamSize == 4 );
			m_vecNormal.push_back( (float)atof( aryParam[1].c_str() ) );
			m_vecNormal.push_back( (float)atof( aryParam[2].c_str() ) );
			m_vecNormal.push_back( (float)atof( aryParam[3].c_str() ) );
		}
		else if ( !strncmp( aryParam[0].c_str(), "mtllib", aryParam[0].size() ) )
		{
			Assert( nParamSize == 2 );
			std::string strMtlFile( aryParam[1].c_str(), aryParam[1].size() );
			if( !CFileManage::Inst().FileIsExist( strMtlFile.c_str() ) )
			{
				strMtlFile = CFileManage::GetFileDir( szFileName ) + strMtlFile;
				if( !CFileManage::Inst().FileIsExist( strMtlFile.c_str() ) )
					continue;
			}

			const SFileStruct* pFile = CFileManage::Inst().Load( strMtlFile.c_str() );
			Assert( pFile );
			OnLoadMtllib( pFile->m_strFileName.c_str(), pFile->m_pBuffer, pFile->m_nSize, mapMaterial );
		}
		else if ( !strncmp( aryParam[0].c_str(), "o", aryParam[0].size() ) )
		{
			Assert( nParamSize == 2 );
			SObjectIndex sIndex;
			sIndex.m_strName.assign( aryParam[1].c_str(), aryParam[1].size() );
			m_vecObject.push_back( sIndex );
		}
		else if ( !strncmp( aryParam[0].c_str(), "usemtl", aryParam[0].size() ) )
		{
			Assert( nParamSize == 2 );
			string szName( aryParam[1].c_str(), aryParam[1].size() );
			Assert( mapMaterial.find( szName ) != mapMaterial.end() );
			CMaterial* pMaterial = mapMaterial[szName];
			m_vecObject.rbegin()->m_Material = pMaterial;
		}
		else if ( !strncmp( aryParam[0].c_str(), "s", aryParam[0].size() ) )
		{
			Assert( nParamSize == 2 );
			if( !strcmp( aryParam[1].c_str(), "1" ) 
				|| !strcmp( aryParam[1].c_str(), "on" ) )
				m_vecObject.rbegin()->m_bSmooth = true;
			else
				m_vecObject.rbegin()->m_bSmooth = false;
		}
		else if ( !strncmp( aryParam[0].c_str(), "f", aryParam[0].size() ) )
		{
			Assert( nParamSize >= 2 );
			cstring aryIndex[5];
			for( uint32 i = 1; i < nParamSize; ++i )
			{
				uint32 nIndexSize = partition( aryParam[i], '/', aryIndex );
				Assert( nIndexSize == 3 );

				m_vecObject.rbegin()->m_vecVertexIndex.push_back( (uint32)atol( aryIndex[0].c_str() ) );
				m_vecObject.rbegin()->m_vecVertexIndex.push_back( (uint32)atol( aryIndex[1].c_str() ) );
				m_vecObject.rbegin()->m_vecVertexIndex.push_back( (uint32)atol( aryIndex[2].c_str() ) );
			}
		}
		else
			Log << "Obj FIle Read Not Realize Keyword : \"" << string( sString.c_str(), sString.size() ) << "\"" << endl;
	}
}

void CDecodeModel::OnLoadMtllib( const char* szFileName, const byte* szBuffer, const uint32 nSize, std::map<std::string, CMaterial*>& mapMaterial )
{
	uint32 nCurPos = 0;
	CMaterial* pCurMaterial = nullptr;
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

		cstring aryParam[10];
		uint32 nParamSize = partition( sString, ' ', aryParam );
		if( nParamSize == 0 )
			continue;

		if ( !strncmp( aryParam[0].c_str(), "#", aryParam[0].size() ) )
			continue;
		else if ( !strncmp( aryParam[0].c_str(), "newmtl", aryParam[0].size() ) )
		{
			string strName( aryParam[1].c_str(), aryParam[1].size() );
			pCurMaterial = CGame::Inst().GetGraphics().CreateResource<CMaterial>();
			mapMaterial[strName] = pCurMaterial;
		}
		else if ( !strncmp( aryParam[0].c_str(), "Ns", aryParam[0].size() ) )
			pCurMaterial->SetShininess( (float)atof( aryParam[1].c_str() ) );
		else if ( !strncmp( aryParam[0].c_str(), "Ka", aryParam[0].size() ) )
		{
			float x = (float)atof( aryParam[1].c_str() );
			float y = (float)atof( aryParam[2].c_str() );
			float z = (float)atof( aryParam[3].c_str() );
			pCurMaterial->SetAmbient( x, y, z );
		}
		else if ( !strncmp( aryParam[0].c_str(), "Kd", aryParam[0].size() ) )
		{
			float x = (float)atof( aryParam[1].c_str() );
			float y = (float)atof( aryParam[2].c_str() );
			float z = (float)atof( aryParam[3].c_str() );
			pCurMaterial->SetDiffuse( x, y, z );
		}
		else if ( !strncmp( aryParam[0].c_str(), "Ks", aryParam[0].size() ) )
		{
			float x = (float)atof( aryParam[1].c_str() );
			float y = (float)atof( aryParam[2].c_str() );
			float z = (float)atof( aryParam[3].c_str() );
			pCurMaterial->SetSpecular( x, y, z );
		}
		else if ( !strncmp( aryParam[0].c_str(), "Ni", aryParam[0].size() ) )
			pCurMaterial->SetRefractiveIndex( (float)atof( aryParam[1].c_str() ) );
		else if ( !strncmp( aryParam[0].c_str(), "d", aryParam[0].size() ) )
			pCurMaterial->SetFadeOut( (float)atof( aryParam[1].c_str() ) );
		else if ( !strncmp( aryParam[0].c_str(), "illum", aryParam[0].size() ) )
			pCurMaterial->SetIllum( atoi( aryParam[1].c_str() ) );
		else if ( !strncmp( aryParam[0].c_str(), "map_Kd", aryParam[0].size() ) )
		{
			string strName( aryParam[1].c_str(), aryParam[1].size() );
			CResourceImg Img;
			CFileManage::Inst().Load( strName.c_str(), Img );
			CTexture2D* pTexture = pCurMaterial->GetTexture( eMaterialTexture_Diffuse );
			pTexture->SetTextureData( Img.GetImageFormat(), Img.GetImageWidth(), Img.GetImageHeight(), Img.GetImageData() );
		}
		else if ( !strncmp( aryParam[0].c_str(), "map_Bump", aryParam[0].size() ) )
		{
			string strName( aryParam[1].c_str(), aryParam[1].size() );
			CResourceImg Img;
			CFileManage::Inst().Load( strName.c_str(), Img );
			CTexture2D* pTexture = pCurMaterial->GetTexture( eMaterialTexture_Bump );
			pTexture->SetTextureData( Img.GetImageFormat(), Img.GetImageWidth(), Img.GetImageHeight(), Img.GetImageData() );
		}
		else if ( !strncmp( aryParam[0].c_str(), "map_Ks", aryParam[0].size() ) )
		{
			string strName( aryParam[1].c_str(), aryParam[1].size() );
			CResourceImg Img;
			CFileManage::Inst().Load( strName.c_str(), Img );
			CTexture2D* pTexture = pCurMaterial->GetTexture( eMaterialTexture_Specular );
			pTexture->SetTextureData( Img.GetImageFormat(), Img.GetImageWidth(), Img.GetImageHeight(), Img.GetImageData() );
		}
	}
}