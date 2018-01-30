#pragma once

struct SModelVector
{
	glm::vec3	m_vPosition;
	glm::vec3	m_vNormal;
	glm::vec2	m_vTexCoords;
};

class CResourceModel
	: public IResourceCallback
{
	std::vector<CResourceImg>		m_vecTexture;
	std::vector<SModelVector>		m_vecVector;
	bool							m_bIsWholeModel;

public:
	CResourceModel();
	~CResourceModel();

	virtual void					OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize );
	void							OnLoadMtllib( const char* szFileName, const byte* szBuffer, const uint32 nSize );
	bool							IsWholeModel() const { return m_bIsWholeModel; }
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

	uint32 ReadLine( char* pBuffer, uint32 nMaxSize )
	{
		Assert( nMaxSize );
		if( m_nCurPos >= m_nMaxSize )
		{
			pBuffer[0] = '\0';
			return 0;
		}
		const char* szStart = m_pBuffer + m_nCurPos;
		uint32 nCurSize = 0;
		while ( szStart[nCurSize] != '\n' && nCurSize + m_nCurPos < m_nMaxSize )
			++nCurSize;
		m_nCurPos += nCurSize + 1;
		if( nCurSize != 0 && szStart[nCurSize-1] == '\r' )
			--nCurSize;
		uint32 nSize = nCurSize < nMaxSize - 1 ? nCurSize : nMaxSize - 1;
		memcpy( pBuffer, szStart, nSize );
		pBuffer[nSize] = '\0';
		return nSize;
	}
};