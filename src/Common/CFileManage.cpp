#include "CFileManage.h"
#include "common.h"
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
	string szFullFileName( m_strRootDir + szFileName );
	errno_t nError = fopen_s( &pFile, szFullFileName.c_str(), "rb" );
	return nError == 0;
}
