#pragma once
/* 只有主相机才会渲染CNode2D */
#include "CNode.h"
#include "CNode2D.h"
#include "CNode3D.h"

class CCamera;

class CScene : public TList<CScene>::INode
{
	TList<CNode>	m_listChilds2D;
	TList<CNode>	m_listChilds3D;
public:
	CScene();
	virtual ~CScene();
	virtual void OnUpdate( uint32 nDeltaTime );

	void AddChild2D( CNode2D& pNode );
	void AddChild3D( CNode3D& pNode );

	void OnRender( CCamera* pCamera );
};

