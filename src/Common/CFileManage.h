#pragma once
#include "TypeDef.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class CResourceType
{
	const byte*				m_pBuffer;
	uint32					m_nBufferSize;
public:
	CResourceType( const byte* szBuffer, uint32 nSize )
		:m_pBuffer( szBuffer )
		, m_nBufferSize( nSize )
	{}
	virtual ~CResourceType() {}

	const byte*				GetBuffer() { return m_pBuffer; }
	uint32					GetSize() { return m_nBufferSize; }
};

class CFileManage
{
	map<string, byte*>		m_mapCache;
	string					m_strRootDir;

	CFileManage();
	~CFileManage();
public:

	static CFileManage&		Inst();
	static string			GetFileNameExtend( const char* szFileName );
	void					Init( const char* szRoot ) { m_strRootDir = szRoot; }

	template<typename ResourceType>
	ResourceType			Load( const char* szFileName );
};

template<typename ResourceType>
ResourceType CFileManage::Load(const char * szFileName)
{
	FILE* pFile;
	string szFullFileName( m_strRootDir + szFileName );
	fopen_s( &pFile, szFullFileName.c_str(), "rb" );

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
		return ResourceType( NULL, 0 );
	}

	pDesData[nSize-1] = NULL;
	m_mapCache[string( szFileName )] = pDesData;
	return ResourceType( pDesData, nSize + 1 );
}