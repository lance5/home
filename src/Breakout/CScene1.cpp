#include "stdafx.h"
#include "Common/CScene.h"
#include "Common/CDecodeModel.h"
#include "Common/CObject3D.h"
#include "CScene1.h"
#include "CSpirit.h"


CScene1::CScene1()
{
	CSpirit* pObject = new CSpirit();
	CDecodeModel ResModel;
	CFileManage::Inst().Load( "nanosuit/nanosuit.obj", ResModel );
	ResModel.FillRenderModel( pObject->GetModel() );
	pObject->SetRatio( CVector3f( 0.05f ) );
	pObject->SetPosition( CVector3f( 0.5, 0.0f, 0.0f ) );

	AddChild( *pObject );
}

CScene1::~CScene1()
{
}
