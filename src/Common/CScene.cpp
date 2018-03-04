#include "CommonHelp.h"
#include "CCamera.h"
#include "CScene.h"

CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::AddCamera( CCamera* pCamera )
{
	m_listCamera.Insert( *pCamera );
}

void CScene::AddChild2D( CNode2D & pNode )
{
	m_listChilds2D.Insert( pNode );
}

void CScene::AddChild3D( CNode3D & pNode )
{
	m_listChilds3D.Insert( pNode );
}

void CScene::OnUpdate( uint32 nDeltaTime )
{
	for ( CNode2D* pNode = m_listChilds2D.GetFirst(); 
		pNode; pNode = pNode->GetNext() )
		pNode->OnUpdate( nDeltaTime );
	for ( CNode3D* pNode = m_listChilds3D.GetFirst(); 
		pNode; pNode = pNode->GetNext() )
		pNode->OnUpdate( nDeltaTime );
}

void CScene::OnRender( CCamera* pCamera )
{

}
