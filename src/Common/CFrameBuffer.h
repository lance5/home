#pragma once

class CTexture2D;

class CFrameBuffer
{
	enum
	{
		eBufferType_Colour,
		eBufferType_Depth,
		eBufferType_Count,
	};
	uint32			m_nFrameBuffer;
	CTexture2D*		m_aryTexture[eBufferType_Count];
public:
	CFrameBuffer( uint32 nWidth, uint32 nHeight );
	~CFrameBuffer();
};