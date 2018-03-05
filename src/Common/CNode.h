#pragma once

#include "TList.h"

class CNode : public TList<CNode>::INode
{
	TList<CNode>	m_ListChilds;
public:
	CNode();
	~CNode();

	void AddChild( CNode& Node );
	void RemoveAllChild();

	virtual void OnUpdate( uint32 nDeltaTime ) = 0;
};

