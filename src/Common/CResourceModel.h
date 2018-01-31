#pragma once

class CResourceModel
	: public IResourceCallback
{
	struct SMaterial
	{
		float						m_fShininess;
		glm::vec3					m_vec3Ambient;
		glm::vec3					m_vec3Diffuse;
		glm::vec3					m_vec3Specular;
		float						m_fRefractiveIndex;
		float						m_fFadeOut;
		uint8						m_nIllum;
		std::string					m_strDiffuse;
		std::string					m_strBump;
		std::string					m_strSpecular;
	};

	struct SObjectIndex
	{
		std::string					m_strName;
		bool						m_bSmooth;
		std::vector<uint32>			m_aryIndex;
		const SMaterial*			m_pMaterial;
	};

	std::vector<float>				m_vecVertex;
	std::vector<float>				m_vecNormal;
	std::vector<float>				m_vecTexCoord;
	bool							m_bIsWholeModel;
	std::vector<SObjectIndex>		m_vecObject;
	std::map<string, SMaterial>		m_mapMaterial;

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