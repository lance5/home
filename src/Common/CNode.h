#pragma once

#include "TList.h"

class CNode : public TList<CNode>::CNode
{
	TList<CNode>	m_ListChilds;
public:
	CNode();
	~CNode();

	void AddChild( CNode& Node );
	void RemoveAllChild();
};

