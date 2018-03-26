#include "CObject3D.h"

CObject3D::CObject3D()
	: m_bUpdateMat( true )
{

}

CObject3D::~CObject3D()
{

}

CMatrix& CObject3D::GetModelMatrix()
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