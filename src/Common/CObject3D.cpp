#include "stdafx.h"
#include "CObject3D.h"
#include "CRenderModel.h"

CObject3D::CObject3D()
	: m_bUpdateMat( true )
	, m_pModelData( new CRenderModel )
{
}

CObject3D::~CObject3D()
{
	SAFE_DELETE( m_pModelData );
}

CRenderModel& CObject3D::GetModel()
{ 
	return *m_pModelData;
}

const CMatrix& CObject3D::GetMatrix()
{
	if( m_bUpdateMat )
	{
		m_bUpdateMat = false;

		CMatrix matMove;
		CMatrix matRatio;
		matMove.SetOffset( m_vPosition );
		matRatio.SetRatio( m_vRatio );
		m_matModel = matRatio * matMove;
	}

	return m_matModel;
}

const CVector3f& CObject3D::GetPosition()
{
	return m_vPosition;
}

void CObject3D::SetPosition( const CVector3f& vPos )
{
	m_bUpdateMat = true;
	m_vPosition = vPos;
}

const CVector3f& CObject3D::GetRatio()
{
	return m_vRatio;
}

void CObject3D::SetRatio( const CVector3f& vRatio )
{
	m_bUpdateMat = true;
	m_vRatio = vRatio;
}
