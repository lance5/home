#pragma once

#include "TList.h"
#include "TVector3.h"
#include "CMatrix.h"

class CRenderModel;

class CObject3D 
	: public TList<CObject3D>::CListNode
{
	CVector3f			m_vPosition;
	CMatrix				m_matModel;
	bool				m_bUpdateMat;
	CRenderModel*			m_pModelData;
	

public:
	CObject3D();
	~CObject3D();
	
	virtual void 		OnUpdate( uint32 nDeltaTime ) = 0;

	const CRenderModel&	GetModel();
	const CMatrix&		GetMatrix();
};

