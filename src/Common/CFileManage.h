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

struct SFileStruct
{
	string			m_strFileName;
	byte*			m_pBuffer;
	uint32			m_nSize;
	SFileStruct() : m_pBuffer( nullptr ) , m_nSize( 0 ) {}
};

class CFileManage
{
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
	const string&					GetRootDir() const { return m_strRootDir; }

	template<typename ResourceType>
	bool							Load( const char* szFileName, ResourceType& pResource );
	const SFileStruct*				Load( const char* szFileName );
};

template<typename ResourceType>
bool CFileManage::Load( const char* szFileName, ResourceType& pResource )
{
	const SFileStruct* pFile = Load( szFileName );
	if( !pFile )
		return false;

	pResource.OnFileLoaded( pFile->m_strFileName.c_str(), pFile->m_pBuffer, pFile->m_nSize );
	return true;
}