#include "CommonHelp.h"

#include "CFileManage.h"
#include "CResourceImg.h"

CFileManage::CFileManage()
{
}


CFileManage::~CFileManage()
{
	for( map<string, SFileStruct>::iterator it = m_mapCache.begin(); it != m_mapCache.end(); ++it )
		SAFE_DELETE_GROUP( it->second.m_pBuffer );
}

CFileManage& CFileManage::Inst()
{
	static CFileManage m_instance;
	return m_instance;
}

string CFileManage::GetFileNameExtend(const char * szFileName)
{
	uint32 nLastPos = INVALIDU32BYTE;
	for (uint32 i = 0; szFileName[i] != '\0'; ++i)
	{
		if (szFileName[i] == '.')
			nLastPos = i;
		Assert( i < INVALIDU32BYTE );
	}
	if( nLastPos == INVALIDU32BYTE )
		return string();
	return string( szFileName + nLastPos + 1 );
}

string CFileManage::GetFileDir(const char * szFullFileName)
{
	uint32 nLen = strlen( szFullFileName );
	uint32 nDirLen = nLen;
	for( ; nDirLen && szFullFileName[nDirLen-1] != '/' && szFullFileName[nDirLen-1] != '\\'; --nDirLen )
		;
	return string( szFullFileName, 0, nDirLen );
}

bool CFileManage::FileIsExist(const char * szFileName)
{
	FILE* pFile;
	errno_t nError = fopen_s( &pFile, szFileName, "rb" );
	return nError == 0;
}

const SFileStruct* CFileManage::Load( const char * szFileName )
{
	if( m_mapCache.find( szFileName ) == m_mapCache.end() )
	{
		string szFullFileName( szFileName );
		if ( !FileIsExist( szFileName ) )
			szFullFileName = m_strRootDir + szFileName;

		FILE* pFile;
		errno_t nError = fopen_s( &pFile, szFullFileName.c_str(), "rb" );
		if( nError != 0 )
			return nullptr;

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
			return nullptr;
		}

		pDesData[nSize] = NULL;
		SFileStruct sFile;
		sFile.m_strFileName = szFullFileName;
		sFile.m_pBuffer = pDesData;
		sFile.m_nSize = nSize + 1;
		m_mapCache[szFileName] = sFile;
	}

	return &( m_mapCache[szFileName] );
}
