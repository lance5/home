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
		matMove.SetOffset( m_vPosition );

		m_matModel = matMove;
	}

	return m_matModel;
}