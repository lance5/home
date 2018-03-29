#include "stdafx.h"
#include "TList.h"
#include "CCamera.h"
#include "CScene.h"

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
	for ( CObject3D* pNode = m_listChilds.GetFirst(); 
		pNode; pNode = pNode->GetNext() )
		pNode->OnUpdate( nDeltaTime );
}

void CScene::OnRender()
{
}
