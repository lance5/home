#pragma once

#include "SModelData.h"

class CResourceModel
	: public IResourceListener
	, private SModelData
{
public:
	CResourceModel();
	~CResourceModel();

	virtual void						OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize );
	void								OnLoadMtllib( const char* szFileName, const byte* szBuffer, const uint32 nSize );

	const SMaterial&					GetMaterial( const char* szString );
	const std::vector<SModelVertex>		GetModelVertex() const { return m_vecModelVertex; }
	const std::vector<SObjectIndex>& 	GetModelObject() const { return m_vecObject; }
};

class CStringBuf
{
	const char*	m_pBuffer;
	uint32		m_nMaxSize;
	uint32		m_nCurPos;

public:
	CStringBuf( const char* pBuffer, uint32 nSize )
		: m_pBuffer( pBuffer )
		, m_nMaxSize( nSize ) {}
	~CStringBuf() {}

	bool ReadLine( char* pBuffer, uint32 nMaxSize )
	{
		Assert( nMaxSize );
		pBuffer[0] = '\0';
		if( m_nCurPos >= m_nMaxSize )
			return false;
		const char* szStart = m_pBuffer + m_nCurPos;
		uint32 nCurSize = 0;
		while ( szStart[nCurSize] != '\n' 
			&& szStart[nCurSize] != '\0' 
			&& nCurSize + m_nCurPos < m_nMaxSize )
			++nCurSize;
		m_nCurPos += nCurSize + 1;
		if( nCurSize != 0 && szStart[nCurSize-1] == '\r' )
			--nCurSize;
		uint32 nSize = nCurSize < nMaxSize - 1 ? nCurSize : nMaxSize - 1;
		memcpy( pBuffer, szStart, nSize );
		pBuffer[nSize] = '\0';
		return ( szStart[0] == '\0' ) ? false : true;
	}
};