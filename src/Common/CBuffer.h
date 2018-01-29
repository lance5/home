#pragma once

#include "TypeDef.h"
#include "common.h"

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

	template<typename DataType>
	void PopData( DataType& Data )
	{
		Read( &Data, sizeof( DataType ) );
	}
};

class CWriteBuffer
{
	byte*			m_pBuffer;
	uint32			m_nCurSize;
	uint32			m_nMaxSize;
public:
	CWriteBuffer()
		: m_pBuffer(NULL)
		, m_nCurSize(0)
		, m_nMaxSize(0)
	{}
	~CWriteBuffer() 
	{
		SAFE_DELETE_GROUP( m_pBuffer );
	}

	void Write( const byte* pData, uint32 nSize )
	{
		if( m_nCurSize + nSize > m_nMaxSize )
		{
			const byte* pTemBuf = m_pBuffer;
			m_nMaxSize = (float)( (float)m_nMaxSize * 1.35f );
			m_pBuffer = new byte[m_nMaxSize];
			Assert( m_pBuffer );
			memset( m_pBuffer, 0, m_nMaxSize );
			memcpy( m_pBuffer, pTemBuf, m_nCurSize );
			if( pTemBuf )
				SAFE_DELETE_GROUP( pTemBuf );
		}

		memcpy( m_pBuffer + m_nCurSize, pData, nSize );
		m_nCurSize += nSize;
	}

	template<typename DataType>
	void PushData( const DataType* pData )
	{
		Write( pData, sizeof( DataType ) );
	}
};