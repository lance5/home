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

void CScene::AddChild( CNode& pNode )
{
	m_listChilds.Insert( pNode );
}

void CScene::AddCamera( CCamera * pCamera )
{
	m_listCamera.Insert( *pCamera );
}

void CScene::OnUpdate( uint32 nDeltaTime )
{
	for ( CNode* pNode = m_listChilds.GetFirst(); 
		pNode; pNode = pNode->GetNext() )
		pNode->OnUpdate( nDeltaTime );
}

void CScene::OnRender()
{
	for ( CCamera* pNode = m_listCamera.GetFirst();
		pNode; pNode = pNode->GetNext() )
		pNode->RenderNode( m_listChilds );
}
