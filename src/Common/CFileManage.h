#pragma once
#include "TypeDef.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class IResourceCallback
{
public:
	virtual void OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize ) = 0;
};

class CFileManage
{
	struct SFileStruct
	{
		string			m_strFileName;
		byte*			m_pBuffer;
		uint32			m_nSize;
		SFileStruct() : m_pBuffer( nullptr ) , m_nSize( 0 ) {}
	};

	map<string, SFileStruct>		m_mapCache;
	string							m_strRootDir;

	CFileManage();
	~CFileManage();
public:

	static CFileManage&				Inst();
	static string					GetFileNameExtend( const char* szFileName );
	static string					GetFileDir( const char* szFullFileName );
	bool							FileIsExist( const char* szFileName );
	void							Init( const char* szRoot ) { m_strRootDir = szRoot; }

	template<typename ResourceType>
	bool							Load( const char * szFileName, ResourceType& pResource );
};

template<typename ResourceType>
bool CFileManage::Load( const char * szFileName, ResourceType& pResource )
{
	string strFileName = string( szFileName );
	if( m_mapCache.find( strFileName ) == m_mapCache.end() )
	{
		FILE* pFile;
		string szFullFileName( m_strRootDir + szFileName );
		errno_t nError = fopen_s( &pFile, szFullFileName.c_str(), "rb" );
		if( nError != 0 )
			return false;

		fseek( pFile, 0, SEEK_END );
		uint32 nSize = (uint32)ftell( pFile );
		fseek( pFile, 0, SEEK_SET );

		byte* pDesData = new byte[nSize + 1];
		memset( pDesData, 0, sizeof( byte ) * ( nSize + 1 ) );
		uint32 nCurSize = fread( &pDesData[0], 1, nSize, pFile );
		fclose( pFile );
		if ( nCurSize != nSize )
		{
			SAFE_DELETE_GROUP( pDesData );
			return false;
		}

		pDesData[nSize] = NULL;
		SFileStruct sFile;
		sFile.m_strFileName = szFullFileName;
		sFile.m_pBuffer = pDesData;
		sFile.m_nSize = nSize + 1;
		m_mapCache[strFileName] = sFile;
	}

	pResource.OnFileLoaded( m_mapCache[strFileName].m_strFileName.c_str(),
		m_mapCache[strFileName].m_pBuffer, m_mapCache[strFileName].m_nSize );
	return true;
}