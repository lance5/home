#include "CommonHelp.h"
#include "TVector3.h"
#include "TMatrix4.h"
#include "CNode.h"
#include "CCamera.h"
#include "CFrameBuffer.h"

CCamera::CCamera( uint32 nNearWdith, uint32 nNearHeight, uint32 nFarLen, float fFov )
	: m_pFrameBuffer( nullptr )
{
	CMatrix4f matrix;
	matrix._11 = 0; matrix._12 = 0; matrix._13 = 0; matrix._14 = 0;
	matrix._21 = 0; matrix._22 = 0; matrix._23 = 0; matrix._24 = 0;
	matrix._31 = 0; matrix._32 = 0; matrix._33 = 0; matrix._34 = 0;
	matrix._41 = 0; matrix._42 = 0; matrix._43 = 0; matrix._44 = 0;
}

CCamera::~CCamera()
{
	SAFE_DELETE( m_pFrameBuffer );
}