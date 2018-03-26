#include "CommonHelp.h"
#include "TVector3.h"
#include "CMatrix.h"
#include "CObject3D.h"
#include "CCamera.h"
#include "CFrameBuffer.h"

CCamera::CCamera( uint32 nNearWdith, uint32 nNearHeight, uint32 nFarLen, float fFov )
	: m_pFrameBuffer( nullptr )
{
}

CCamera::~CCamera()
{
	SAFE_DELETE( m_pFrameBuffer );
}

void CCamera::RenderNode( TList<CObject3D>& listNode )
{

}