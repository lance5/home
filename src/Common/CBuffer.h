#pragma once

class CReadBuffer
{
	const byte*		m_pBuffer;
	uint32			m_nCurPos;
	const uint32	m_nMaxSize;
public:
	CReadBuffer(const byte * pBuffer, uint32 nMaxSize)
		: m_pBuffer( pBuffer )
		, m_nMaxSize( nMaxSize )
		, m_nCurPos( 0 )
	{
		Assert( pBuffer );
		Assert( nMaxSize );
	}
	~CReadBuffer() {}

	void Read( byte* pData, uint32 nSize )
	{
		Assert( m_nCurPos + nSize <= m_nMaxSize );
		memcpy( pData, m_pBuffer + m_nCurPos, nSize );
		m_nCurPos += nSize;
	}

	bool ReadLine( char* pBuffer, uint32 nMaxSize )
	{
		Assert( nMaxSize );
		pBuffer[0] = '\0';
		if( m_nCurPos >= m_nMaxSize )
			return false;
		const byte* szStart = m_pBuffer + m_nCurPos;
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

	template<typename DataType>
	void PopData( DataType& Data )
	{
		Read( &Data, sizeof( DataType ) );
	}
};

class CWriteBuffer
{
	byte*			m_pBuffer;
	uint32			m_nCurPos;
	uint32			m_nMaxSize;
public:
	CWriteBuffer()
		: m_pBuffer(NULL)
		, m_nCurPos(0)
		, m_nMaxSize(0)
	{}
	~CWriteBuffer() 
	{
		SAFE_DELETE_GROUP( m_pBuffer );
	}

	void Write( const byte* pData, uint32 nSize )
	{
		if( m_nCurPos + nSize > m_nMaxSize )
		{
			const byte* pTemBuf = m_pBuffer;
			m_nMaxSize = (uint32)( (float)m_nMaxSize * 1.35f );
			m_pBuffer = new byte[m_nMaxSize];
			Assert( m_pBuffer );
			memset( m_pBuffer, 0, m_nMaxSize );
			memcpy( m_pBuffer, pTemBuf, m_nCurPos );
			if( pTemBuf )
				SAFE_DELETE_GROUP( pTemBuf );
		}

		memcpy( m_pBuffer + m_nCurPos, pData, nSize );
		m_nCurPos += nSize;
	}

	template<typename DataType>
	void PushData( const DataType* pData )
	{
		Write( pData, sizeof( DataType ) );
	}
};