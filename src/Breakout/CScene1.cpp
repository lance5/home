#include "stdafx.h"
#include "Common/CScene.h"
#include "Common/CDecodeModel.h"
#include "CScene1.h"
#include "CSpirit.h"


CScene1::CScene1()
{
	CSpirit* pObject = new CSpirit();
	CDecodeModel ResModel;
	CFileManage::Inst().Load( "nanosuit/nanosuit.obj", ResModel );
	ResModel.FillRenderModel( pObject->GetModel() );

	AddChild( *pObject );
}


CScene1::~CScene1()
{
}
