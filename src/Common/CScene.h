#pragma once
#include "CObject3D.h"

class CCamera;
class CGraphics;

class CScene : public TList<CScene>::CListNode
{
	TList<CObject3D>	m_listChilds;
	TList<CCamera>		m_listCamera;
public:
	CScene();
	virtual ~CScene();
	virtual void OnUpdate( uint32 nDeltaTime );

	void AddChild( CObject3D& pNode );
	void AddCamera( CCamera* pCamera );

	void OnRender( CGraphics* pGraphics );
};

