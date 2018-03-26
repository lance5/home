#pragma once

#include "TList.h"
#include "TVector3.h"
#include "CMatrix.h"
#include "SModelData.h"

class CObject3D 
	: public TList<CObject3D>::CListNode
	, private SModelData
{
	CVector3f			m_vPosition;
	CMatrix				m_matModel;
	bool				m_bUpdateMat;

	

public:
	CObject3D() {}
	~CObject3D() {}
	
	virtual void 		OnUpdate( uint32 nDeltaTime ) = 0;

	CMatrix&			GetModelMatrix();
};

