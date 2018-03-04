#pragma once
/* 只有主相机才会渲染CNode2D */
#include "CNode.h"
#include "CNode2D.h"
#include "CNode3D.h"

class CCamera;

class CScene : public CNode
{
	TList<CNode2D>	m_listChilds2D;
	TList<CNode3D>	m_listChilds3D;
public:
	CScene();
	~CScene();

	void AddChild2D( CNode2D& pNode );
	void AddChild3D( CNode3D& pNode );

	virtual void OnUpdate( uint32 nDeltaTime );
	void OnRender( CCamera* pCamera );
};

