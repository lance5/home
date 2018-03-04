#include "CommonHelp.h"
#include "CNode.h"

CNode::CNode()
{
}


CNode::~CNode()
{
}

void CNode::AddChild(CNode & Node)
{
	m_ListChilds.Insert( Node );
}

void CNode::RemoveAllChild()
{
	while( !m_ListChilds.IsEmpty() )
		m_ListChilds.GetFirst()->Remove();
}
