#pragma once

#include "TList.h"

class CNode : public TList<CNode>::INode
{
	TList<CNode>	m_ListChilds;
public:
	CNode() {}
	~CNode() {}

	virtual void OnUpdate( uint32 nDeltaTime ) = 0;

	void AddChild( CNode & Node )
	{
		m_ListChilds.Insert( Node );
	}

	void RemoveAllChild()
	{
		while( !m_ListChilds.IsEmpty() )
			m_ListChilds.GetFirst()->Remove();
	}
};

