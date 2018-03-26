#pragma once

class CFrameBuffer;

class CCamera : public TList<CCamera>::CListNode
{
	CVector3f			m_vecPosition;
	CVector3f			m_vecLookPosition;
	CVector3f			m_vecUpDir;

	uint32				m_nNearWidth;
	uint32				m_nNearHeight;
	uint32				m_nFarLen;
	float				m_fFov;

	CFrameBuffer*		m_pFrameBuffer;
public:
	CCamera( uint32 nNearWdith, uint32 nNearHeight, uint32 nFarLen, float fFov );
	~CCamera();
};