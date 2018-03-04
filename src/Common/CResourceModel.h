#pragma once

struct SMaterial
{
	float						m_fShininess;
	CVector3f					m_vec3Ambient;
	CVector3f					m_vec3Diffuse;
	CVector3f					m_vec3Specular;
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

struct SModelVertex
{
	float						m_aryVertex[3];
	float						m_aryNoram[3];
	float						m_aryTexCoord[2];
};

class CResourceModel
	: public IResourceCallback
{
	std::vector<SModelVertex>		m_vecModelVertex;
	std::vector<SObjectIndex>		m_vecObject;
	std::map<std::string,SMaterial> m_mapMaterial;

public:
	CResourceModel();
	~CResourceModel();

	virtual void					OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize );
	void							OnLoadMtllib( const char* szFileName, const byte* szBuffer, const uint32 nSize );

	const std::vector<SModelVertex>	GetModelVertex() const { return m_vecModelVertex; }
	const std::vector<SObjectIndex>& GetModelObject() const { return m_vecObject; }
	const SMaterial&				GetMaterial( const char* szString );
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