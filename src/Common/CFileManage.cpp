#include "CFileManage.h"
#include "common.h"
#include "CResourceImg.h"

CFileManage::CFileManage()
{
}


CFileManage::~CFileManage()
{
	for( map<string, byte*>::iterator it = m_mapCache.begin(); it != m_mapCache.end(); ++it )
		SAFE_DELETE_GROUP( it->second );
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