#include "stdafx.h"
#include "TList.h"
#include "CCamera.h"
#include "CScene.h"
#include "CGame.h"
#include "CGraphics.h"

CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::AddChild( CObject3D& pNode )
{
	m_listChilds.Insert( pNode );
}

void CScene::AddCamera( CCamera * pCamera )
{
	m_listCamera.Insert( *pCamera );
}

void CScene::OnUpdate( uint32 nDeltaTime )
{

}

void CScene::OnRender( CGraphics* pGraphics )
{
	//pGraphics->RenderTest();
	//return;
	for ( CObject3D* pNode = m_listChilds.GetFirst(); pNode; pNode = pNode->GetNext() )
	{
		pGraphics->RenderObject( eShaderType_Sprite, pNode->GetModel(), pNode->GetMatrix() );
	}
}
