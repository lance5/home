#pragma once

#include "TList.h"
#include "TVector3.h"
#include "CMatrix.h"

class CRenderModel;

class CObject3D 
	: public TList<CObject3D>::CListNode
{
	CVector3f			m_vPosition;
	CVector3f			m_vRatio;
	CMatrix				m_matModel;
	bool				m_bUpdateMat;
	CRenderModel*		m_pModelData;
	

public:
	CObject3D();
	~CObject3D();

	CRenderModel&		GetModel();
	const CMatrix&		GetMatrix();

	const CVector3f&	GetPosition();
	const CVector3f&	GetRatio();

	void				SetPosition( const CVector3f& vPos );
	void				SetRatio( const CVector3f& vRatio );
};

